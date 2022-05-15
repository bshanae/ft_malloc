#ifndef BLOCK
#define BLOCK

#include <stdlib.h>
#include "libft_standart.h"

struct block_header
{
	t_bool is_allocated;
	size_t payload_size;

	// If block is allocated, these pointers are invalid
	struct block_header *previous;
	struct block_header *next;
};

struct block_footer
{
	size_t payload_size;
};

// SIZE

size_t block_get_meta_size();
size_t block_compute_complete_size(size_t payload_size);

// NAVIGATION

void *block_get_payload_from_header(struct block_header *header);
struct block_header *block_get_header_from_payload(void *payload);
struct block_header *block_get_header_from_footer(struct block_footer *footer);
struct block_footer *block_get_footer_from_header(struct block_header *header);
struct block_footer *block_get_previous_footer(struct block_header *header);
struct block_header *block_get_next_header(struct block_footer *footer);

// LIST

struct block_header *block_find_first(struct block_header *node);
struct block_header *block_find_last(struct block_header *node);
void block_link(struct block_header *first, struct block_header *second);
void block_insert_before(struct block_header *next, struct block_header *value);

#endif
