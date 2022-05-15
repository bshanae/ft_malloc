#include "block.h"

#include <unistd.h>

// SIZE --------------------------------------------------------------------------------------------------------------------------------------------------------

size_t block_get_meta_size()
{
	return sizeof(struct block_header) + sizeof(struct block_footer);
}

size_t block_compute_complete_size(size_t payload_size)
{
	return payload_size + block_get_meta_size();
}

// NAVIGATION --------------------------------------------------------------------------------------------------------------------------------------------------

void *block_get_payload_from_header(struct block_header *header)
{
	return ((char *)header) + sizeof(struct block_header);
}

struct block_header *block_get_header_from_payload(void *payload)
{
	return (void *)((char *)payload - sizeof(struct block_header));
}

struct block_header *block_get_header_from_footer(struct block_footer *footer)
{
	return (void *)((char *)footer - footer->payload_size - sizeof(struct block_header));
}

struct block_footer *block_get_footer_from_header(struct block_header *header)
{
	return (void *)((char *)header + sizeof(struct block_header) + header->payload_size);
}

struct block_footer *block_get_previous_footer(struct block_header *header)
{
	return (void *)((char *)header - sizeof(struct block_footer));
}

struct block_header *block_get_next_header(struct block_footer *footer)
{
	return (void *)((char *)footer + sizeof(struct block_footer));
}

// LIST --------------------------------------------------------------------------------------------------------------------------------------------------------

struct block_header *block_find_first(struct block_header *node)
{
	if (node == NULL)
		return NULL;

	while (node->previous != NULL)
		node = node->previous;

	return node;
}

struct block_header *block_find_last(struct block_header *node)
{
	if (node == NULL)
		return NULL;

	while (node->next != NULL)
		node = node->next;

	return node;
}

void block_link(struct block_header *first, struct block_header *second)
{
	if (first != NULL)
		first->next = second;

	if (second != NULL)
		second->previous = first;
}

void block_insert_before(struct block_header *next, struct block_header *value)
{
	struct block_header *previous = next->previous;

	value->next = next;
	value->previous = previous;

	next->previous = value;

	if (previous != NULL)
		previous->next = value;
}