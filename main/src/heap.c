#include "heap.h"

#include <sys/mman.h>
#include "utility_memory.h"

// INTERNAL FUNCTIONS ------------------------------------------------------------------------------------------------------------------------------------------

static t_bool try_coalesce_with_left_block(struct heap *heap, struct block_header **main_header)
{
	struct block_footer *left_footer = block_get_previous_footer(*main_header);
	if (!heap_does_include_ptr(heap, left_footer))
		return false;

	struct block_header *left_header = block_get_header_from_footer(left_footer);
	if (left_header->is_allocated)
		return false;

	left_header->payload_size += (*main_header)->payload_size + block_get_meta_size();
	block_get_footer_from_header(left_header)->payload_size = left_header->payload_size;

	*main_header = left_header;

	return true;
}

static t_bool try_coalesce_with_right_block(struct heap *heap, struct block_header *main_header)
{
	struct block_footer *main_footer = block_get_footer_from_header(main_header);

	struct block_header *right_header = block_get_next_header(main_footer);
	if (!heap_does_include_ptr(heap, right_header))
		return false;
	if (right_header->is_allocated)
		return false;

	main_header->payload_size += right_header->payload_size + block_get_meta_size();
	block_get_footer_from_header(main_header)->payload_size = main_header->payload_size;

	if (right_header->previous != main_header)
		block_link(right_header->previous, main_header);
	block_link(main_header, right_header->next);

	if (heap->free_blocks == right_header)
		heap->free_blocks = main_header;

	return true;
}

static void insert_freed_block_into_free_list(struct heap *heap, struct block_header *freed_block)
{
	if (heap->free_blocks != NULL) // Regular case
	{
		// Find proper place for freed block
		struct block_header *next_block = NULL;
		for (struct block_header *iterator = heap->free_blocks; iterator != NULL; iterator = iterator->next)
		{
			if (iterator > freed_block)
			{
				next_block = iterator;
				break;
			}
		}

		if (next_block != NULL)
		{
			// Found next block, insert free block before it
			block_insert_before(next_block, freed_block);
		}
		else
		{
			// Next block not found, freed block should be last block in free list
			block_link(block_find_last(heap->free_blocks), freed_block);
		}

		// Restore list head
		heap->free_blocks = block_find_first(heap->free_blocks);
	}
	else // Special case
	{
		heap->free_blocks = freed_block;
		return;
	}
}

static void process_freed_block(struct heap *heap, struct block_header **header)
{
	heap->free_payload_size += (*header)->payload_size + block_get_meta_size();

	(*header)->previous = NULL;
	(*header)->next = NULL;

	const t_bool have_coalesced_leftward = try_coalesce_with_left_block(heap, header);
	const t_bool have_coalesced_rightward = try_coalesce_with_right_block(heap, *header);

	if (!have_coalesced_leftward && !have_coalesced_rightward)
		insert_freed_block_into_free_list(heap, *header);
}

t_bool try_enlarge_block(struct heap *heap, struct block_header *block, size_t desired_payload_size)
{
	struct block_header *this_header = block;
	struct block_header *next_header = block_get_next_header(block_get_footer_from_header(this_header));

	if (!heap_does_include_ptr(heap, next_header))
		return false;

	if (next_header->is_allocated)
		return false;

	// Select strategy for enlargement:
	//   1. merge two blocks: h@fh#f -> h@@f
	//   2. enlarge first block, lessen second block: h@fh##f -> h@@fh#f
	// '#' - free memory, '@' - allocated memory, 'h' - header, 'f' - footer.

	const size_t payload_size_with_one_block = this_header->payload_size + next_header->payload_size + block_get_meta_size();
	const size_t payload_size_with_two_blocks = this_header->payload_size + next_header->payload_size;

	const t_bool use_one_block = payload_size_with_one_block == desired_payload_size;
	const t_bool use_two_blocks = !use_one_block;

	// Check if second strategy can be used.

	if (use_two_blocks && payload_size_with_two_blocks < desired_payload_size)
		return false;

	// Update heap meta.

	if (use_one_block && heap->free_blocks == next_header)
		heap->free_blocks = next_header->next;

	if (use_one_block)
		heap->free_payload_size -= next_header->payload_size + block_get_meta_size();
	else if (use_two_blocks)
		heap->free_payload_size -= desired_payload_size - this_header->payload_size;

	// Cache second header in case it will be affected by actions on this header.

	struct block_header next_header_cached = *next_header;

	// Update first block.

	this_header->payload_size = desired_payload_size;

	struct block_footer *this_footer = block_get_footer_from_header(this_header);
	this_footer->payload_size = desired_payload_size;

	// If first strategy is used, connect two neighbor free blocks.

	if (use_one_block)
		block_link(next_header->previous, next_header->next);

	// Update second block, if second strategy is used.

	if (use_two_blocks)
	{
		struct block_header *next_header_shifted = block_get_next_header(this_footer);
		next_header_shifted->is_allocated = false;
		next_header_shifted->payload_size = payload_size_with_two_blocks - desired_payload_size;
		next_header_shifted->previous = next_header_cached.previous;
		next_header_shifted->next = next_header_cached.next;

		struct block_footer *next_footer = block_get_footer_from_header(next_header_shifted);
		next_footer->payload_size = next_header_shifted->payload_size;

		block_link(next_header_cached.previous, next_header_shifted);
		block_link(next_header_shifted, next_header_cached.next);

		if (heap->free_blocks == next_header)
			heap->free_blocks = next_header_shifted;
	}

	return true;
}

t_bool lessen_block_by_splitting(struct heap *heap, struct block_header *block, size_t desired_payload_size)
{
	// Check if splitting is possible

	const size_t minimal_left_size = 1;

	if (block->payload_size < desired_payload_size + block_get_meta_size() + minimal_left_size)
	{
		// Can't split block. Not enough space for meta of second block or for minimal payload.
		return false;
	}

	// Calculate sizes

	struct block_header *first_header = block;

	const size_t first_block_size = desired_payload_size;
	const size_t second_block_size = first_header->payload_size - desired_payload_size - block_get_meta_size();

	// Setup first block

	first_header->payload_size = first_block_size;

	struct block_footer *first_footer = block_get_footer_from_header(first_header);
	first_footer->payload_size = desired_payload_size;

	// Setup second block

	struct block_header *second_header = block_get_next_header(first_footer);
	second_header->is_allocated = false;
	second_header->payload_size = second_block_size;
	second_header->previous = NULL;
	second_header->next = NULL;

	struct block_footer *second_footer = block_get_footer_from_header(second_header);
	second_footer->payload_size = second_block_size;

	process_freed_block(heap, &second_header);
	return true;
}

// LIST MANIPULATION -------------------------------------------------------------------------------------------------------------------------------------------

void heap_append(struct heap *base, struct heap *child)
{
	if (base == NULL)
		return;

	while (base->next != NULL)
		base = base->next;

	base->next = child;
	child->previous = base;
}

void heap_remove(struct heap *target)
{
	if (target->previous != NULL)
		target->previous->next = target->next;

	if (target->next != NULL)
		target->next->previous = target->previous;

	target->previous = NULL;
	target->next = NULL;
}

// HEAP MANIPULATION -------------------------------------------------------------------------------------------------------------------------------------------

struct heap *heap_preallocate(size_t min_block_payload_size, size_t max_block_payload_size, size_t number_of_blocks)
{
	struct heap *heap = heap_allocate(min_block_payload_size, max_block_payload_size, number_of_blocks);
	heap->is_preallocated = true;

	return heap;
}

struct heap *heap_allocate(size_t min_block_payload_size, size_t max_block_payload_size, size_t number_of_blocks)
{
	// Compute heap size

	const size_t heap_size = heap_compute_size(max_block_payload_size, number_of_blocks);
	if (heap_size > get_allocation_limit())
		return NULL;

	// Request memory

	char *ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;

	struct heap *heap = (struct heap *)ptr;

	// Initialize instance

	heap->is_preallocated = false;
	heap->min_block_payload_size = min_block_payload_size;
	heap->max_block_payload_size = max_block_payload_size;

	heap->total_payload_size = heap_size - heap_get_meta_size();
	heap->free_payload_size = heap->total_payload_size;

	heap->next = NULL;
	heap->previous = NULL;

	// Create block that occupies all of heap's payload

	heap->free_blocks = heap_get_begin(heap);

	heap->free_blocks->is_allocated = false;
	heap->free_blocks->payload_size = heap->total_payload_size - block_get_meta_size();
	heap->free_blocks->previous = NULL;
	heap->free_blocks->next = NULL;

	block_get_footer_from_header(heap->free_blocks)->payload_size = heap->free_blocks->payload_size;

	return heap;
}

void heap_deallocate(struct heap *heap)
{
	heap->min_block_payload_size = 0;
	heap->max_block_payload_size = 0;
	heap->total_payload_size = 0;
	heap->free_payload_size = 0;
	heap->free_blocks = NULL;
	heap->previous = NULL;
	heap->next = NULL;

	munmap(heap, heap->total_payload_size + heap_get_meta_size());
}

// BLOCK MANIPULATION ------------------------------------------------------------------------------------------------------------------------------------------

void *heap_allocate_block(struct heap *heap, size_t requested_payload_size)
{
	// Find block with enough payload

	struct block_header *suitable_block = NULL;
	for (struct block_header *iterator = heap->free_blocks; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->payload_size >= requested_payload_size)
		{
			suitable_block = iterator;
			break;
		}
	}

	// If block is not found, return NULL

	if (suitable_block == NULL)
		return NULL;

	// Check if splitting is needed.

	if (suitable_block->payload_size == requested_payload_size)
	{
		// If requested size is equals to actual block size, simply remove it from free list.

		suitable_block->is_allocated = true;

		block_link(suitable_block->previous, suitable_block->next);
		if (heap->free_blocks == suitable_block)
			heap->free_blocks = suitable_block->next;
	}
	else
	{
		// Check if splitting is possible.

		if (block_get_meta_size() + requested_payload_size >= suitable_block->payload_size)
			return NULL;

		// Split suitable block into allocated and free blocks.
		// h##f -> h@fh#f
		// '#' - free memory, '@' - allocated memory, 'h' - header, 'f' - footer.

		// Find pointers

		struct block_header *allocated_block_header = suitable_block;
		struct block_footer *allocated_block_footer = (void *)((char *)suitable_block + sizeof(struct block_header) + requested_payload_size);

		struct block_header *free_block_header = block_get_next_header(allocated_block_footer);
		struct block_footer *free_block_footer = block_get_footer_from_header(suitable_block);

		// Setup free block

		free_block_header->is_allocated = false;
		free_block_header->payload_size = suitable_block->payload_size - requested_payload_size - block_get_meta_size();

		block_link(suitable_block->previous, free_block_header);
		block_link(free_block_header, suitable_block->next);
		if (heap->free_blocks == suitable_block)
			heap->free_blocks = free_block_header;

		free_block_footer->payload_size = free_block_header->payload_size;

		// Setup allocated block

		allocated_block_header->is_allocated = true;
		allocated_block_header->payload_size = requested_payload_size;

		allocated_block_footer->payload_size = requested_payload_size;
	}

	heap->free_payload_size -= requested_payload_size + block_get_meta_size();

	return block_get_payload_from_header(suitable_block);
}

void heap_free_block(struct heap *heap, void *ptr)
{
	struct block_header *header = block_get_header_from_payload(ptr);
	header->is_allocated = false;

	process_freed_block(heap, &header);
}

t_bool heap_try_resize_block(struct heap *heap, void *ptr, size_t desired_payload_size)
{
	struct block_header *this_header = block_get_header_from_payload(ptr);

	if (desired_payload_size > this_header->payload_size)
		return try_enlarge_block(heap, this_header, desired_payload_size);
	if (desired_payload_size < this_header->payload_size)
		return lessen_block_by_splitting(heap, this_header, desired_payload_size);

	// Resize on same size... Why?
	return true;
}

// SIZE --------------------------------------------------------------------------------------------------------------------------------------------------------

size_t heap_get_meta_size()
{
	return sizeof(struct heap);
}

size_t heap_compute_size(size_t block_payload_size, size_t number_of_blocks)
{
	const size_t page_size = getpagesize();

	const size_t desired_heap_size = block_compute_complete_size(block_payload_size) * number_of_blocks + heap_get_meta_size();
	const size_t rounder_heap_size = (desired_heap_size / page_size + 1) * page_size;

	return rounder_heap_size;
}

// NAVIGATION --------------------------------------------------------------------------------------------------------------------------------------------------

void *heap_get_begin(struct heap *heap)
{
	return (void *)((char *)heap + sizeof(struct heap));
}

void *heap_get_end(struct heap *heap)
{
	return heap_get_begin(heap) + heap->total_payload_size;
}

t_bool heap_does_include_ptr(struct heap *heap, void *ptr)
{
	return ptr >= heap_get_begin(heap) && ptr < heap_get_end(heap);
}

// UTILITIES ---------------------------------------------------------------------------------------------------------------------------------------------------

t_bool heap_is_empty(struct heap *heap)
{
	return heap->total_payload_size == heap->free_payload_size;
}

t_bool heap_is_suitable_for_allocation(struct heap *heap, size_t requested_block_size)
{
	if (requested_block_size < heap->min_block_payload_size || requested_block_size > heap->max_block_payload_size)
		return false;
	if (requested_block_size + block_get_meta_size() > heap->free_payload_size)
		return false;

	return true;
}