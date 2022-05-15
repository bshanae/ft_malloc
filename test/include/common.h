#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include "malloc.h"
#include "malloc_debug.h"
#include "utility_io.h"

#define _STR(a) #a
#define STR(a) _STR(a)

#define _CONCAT_2(a, b) a ## b
#define CONCAT_2(a, b) _CONCAT_2(a, b)

#define _CONCAT_3(a, b, c) a ## b ## c
#define CONCAT_3(a, b, c) _CONCAT_3(a, b, c)

extern enum debug_mode debug_mode;

static inline void exit_with_message(const char *message)
{
	write_str(ANSI_RED);
	write_str(message);
	write_str(ANSI_RESET);

	exit(1);
}

static inline int random_int()
{
	static unsigned int seed = 42;

	unsigned int r = seed;

	r ^= r << 13;
	r ^= r >> 17;
	r ^= r << 5;

	seed = r;

	return (int) (r & 2147483647);
}

static inline int random_int_in_range(int min, int max)
{
	return random_int() % (max - min) + min;
}

static inline void warm_up_heaps()
{
	free(malloc(1));
}

static inline void litter_heaps()
{
	const size_t allocations_count = 10000;
	const size_t allocation_size = 16;

	char *ptrs[allocations_count];

	for (size_t i = 0; i < allocations_count; i++)
		ptrs[i] = malloc(allocation_size);
	for (size_t i = 0; i < allocations_count; i++)
		free(ptrs[i]);
}

static inline void validate_intermediate_state()
{
	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		size_t free_payload_size = 0;
		for (struct block_header *header = heap->free_blocks; header != NULL; header = header->next)
			free_payload_size += header->payload_size + block_get_meta_size();

		if (heap->free_payload_size != free_payload_size)
		{
			write_ptr(heap);
			exit_with_message("Intermediate state is invalid. Free payload size is invalid.");
		}
	}
}

static inline void validate_clean_state()
{
	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		if (!heap->is_preallocated)
			exit_with_message("Clean state is invalid. Found non-preallocated heap.");
		if (heap->total_payload_size != heap->free_payload_size)
			exit_with_message("Clean state is invalid. Found heap with invalid free payload size.");

		struct block_header *free_blocks = heap->free_blocks;
		if (free_blocks == NULL)
			exit_with_message("Clean state is invalid. Free block is null.");
		if (free_blocks->payload_size != heap->total_payload_size - block_get_meta_size())
			exit_with_message("Clean state is invalid. Free block has invalid size.");
		if (free_blocks->next != NULL || free_blocks->previous != NULL)
			exit_with_message("Clean state is invalid. Free block has invalid links.");
	}
}

#endif