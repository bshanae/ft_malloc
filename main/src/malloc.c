#include "malloc.h"
#include "utility.h"

struct heap *heaps;

void free(void *ptr)
{
	if (ptr == NULL)
		return;

	if (heaps == NULL)
		return;

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		if (heap_does_include_ptr(heap, ptr))
		{
			heap_free_block(heap, ptr);

			if (!heap->is_preallocated && heap_is_empty(heap))
			{
				heap_remove(heap);
				heap_deallocate(heap);
			}

			return;
		}
	}
}

void *malloc(size_t size)
{
	if (size == 0)
		return NULL;

	// Check for size_t overflow
	if (size + block_get_meta_size() < size)
		return NULL;

	if (heaps == NULL)
	{
		// Initialize heaps
		heaps = heap_preallocate(TINY_BLOCK_MIN_PAYLOAD_SIZE, TINY_BLOCK_MAX_PAYLOAD_SIZE, BLOCKS_IN_PREALLOCATED_HEAP);
		heap_append(heaps, heap_preallocate(SMALL_BLOCK_MIN_PAYLOAD_SIZE, SMALL_BLOCK_MAX_PAYLOAD_SIZE, BLOCKS_IN_PREALLOCATED_HEAP));
	}

	struct heap *heap = NULL;
	void *result = NULL;

	if (size >= LARGE_BLOCK_MIN_PAYLOAD_SIZE)
	{
		// Generate large block
		heap = heap_allocate(size + block_get_meta_size(), size + block_get_meta_size(), 1);
		heap_append(heaps, heap);
	}
	else
	{
		for (heap = heaps; heap != NULL; heap = heap->next)
		{
			if (heap_is_suitable_for_allocation(heap, size))
			{
				result = heap_allocate_block(heap, size);
				if (result != NULL)
					return result;
			}
		}

		// If suitable heap is not found, create new heap for either tiny or small blocks
		if (size < TINY_BLOCK_MAX_PAYLOAD_SIZE)
		{
			heap = heap_allocate(TINY_BLOCK_MIN_PAYLOAD_SIZE, TINY_BLOCK_MAX_PAYLOAD_SIZE, BLOCKS_IN_PREALLOCATED_HEAP);
			heap_append(heaps, heap);
		}
		else if (size < SMALL_BLOCK_MAX_PAYLOAD_SIZE)
		{
			heap = heap_allocate(SMALL_BLOCK_MIN_PAYLOAD_SIZE, SMALL_BLOCK_MAX_PAYLOAD_SIZE, BLOCKS_IN_PREALLOCATED_HEAP);
			heap_append(heaps, heap);
		}
	}

	// Heap not found and can't be created.
	if (heap == NULL)
		return NULL;

	return heap_allocate_block(heap, size);
}

void *realloc(void *ptr, size_t size)
{
	if (size == 0)
		return NULL;

	// Try to resize corresponding block

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		if (heap_does_include_ptr(heap, ptr))
		{
			if (heap_try_resize_block(heap, ptr, size))
				return ptr;
			else
				break;
		}
	}

	// Address is invalid or resizing can't be done

	void *new_ptr = malloc(size);

	if (new_ptr != NULL && ptr != NULL)
	{
		const size_t previous_size = block_get_header_from_payload(ptr)->payload_size;
		ft_memcpy(new_ptr, ptr, MIN(previous_size, size));
	}

	free(ptr);

	return new_ptr;
}