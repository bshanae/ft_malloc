#ifndef HEAP
#define HEAP

#include "libft_standart.h"
#include "block.h"

struct heap
{
	// Preallocated heaps are not deleted, when they are empty
	t_bool is_preallocated;

	size_t min_block_payload_size;
	size_t max_block_payload_size;

	size_t total_payload_size;

	// This value includes free blocks meta
	size_t free_payload_size;

	struct heap *previous;
	struct heap *next;

	struct block_header *free_blocks;
};

// LIST

void heap_append(struct heap *base, struct heap *child);
void heap_remove(struct heap *target);

// HEAP MANIPULATION

struct heap *heap_preallocate(size_t min_block_payload_size, size_t max_block_payload_size, size_t number_of_blocks);
struct heap *heap_allocate(size_t min_block_payload_size, size_t max_block_payload_size, size_t number_of_blocks);
void heap_deallocate(struct heap *heap);

// BLOCK MANIPULATION

void *heap_allocate_block(struct heap *heap, size_t requested_payload_size);
void heap_free_block(struct heap *heap, void *ptr);
t_bool heap_try_resize_block(struct heap *heap, void *ptr, size_t desired_payload_size);

// SIZE

size_t heap_get_meta_size();
size_t heap_compute_size(size_t block_payload_size, size_t number_of_blocks);

// NAVIGATION

void *heap_get_begin(struct heap *heap);
void *heap_get_end(struct heap *heap);
t_bool heap_does_include_ptr(struct heap *heap, void *ptr);

// UTILITIES

t_bool heap_is_empty(struct heap *heap);
t_bool heap_is_suitable_for_allocation(struct heap *heap, size_t requested_block_size);

#endif