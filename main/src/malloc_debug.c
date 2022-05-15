#include "malloc_debug.h"

#include "utility_memory.h"
#include "utility_io.h"

void show_alloc_mem()
{
	size_t total_allocated_memory = 0;

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		if (heap->min_block_payload_size == TINY_BLOCK_MIN_PAYLOAD_SIZE)
			write_str("TINY : ");
		else if (heap->min_block_payload_size == SMALL_BLOCK_MIN_PAYLOAD_SIZE)
			write_str("SMALL : ");
		else if (heap->min_block_payload_size >= LARGE_BLOCK_MIN_PAYLOAD_SIZE)
			write_str("LARGE : ");
		else
			write_str("? : ");

		write_ptr(&heap->free_blocks);
		write_break();

		for (struct block_header *header = heap_get_begin(heap); heap_does_include_ptr(heap, header); header = block_get_next_header(
			block_get_footer_from_header(header)))
		{
			if (!header->is_allocated)
				continue;

			const void *payload = block_get_payload_from_header(header);
			const void *footer = block_get_footer_from_header(header);

			const size_t payload_size = footer - payload;

			write_ptr(payload);
			write_str(" - ");
			write_ptr(footer);
			write_str(" : ");
			write_ulong(payload_size, 10, false);
			write_str(" bytes");
			write_break();

			total_allocated_memory += payload_size;
		}
	}

	write_str("Total : ");
	write_ulong(total_allocated_memory, 10, false);
	write_str(" bytes");
	write_break();
}

void show_alloc_mem_ex(const char *message)
{
	if (message != NULL)
	{
		write_str(ANSI_BOLD);
		write_str(message);
		write_str(ANSI_RESET);
		write_break();
	}

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		write_str("== HEAP =======================================================================");
		write_break();

		write_str("is preallocated : ");
		write_bool(heap->is_preallocated);
		write_break();

		write_str("min block payload size : ");
		write_ulong(heap->min_block_payload_size, 10, false);
		write_break();

		write_str("max block payload size : ");
		write_ulong(heap->max_block_payload_size, 10, false);
		write_break();

		if (heap->min_block_payload_size == TINY_BLOCK_MIN_PAYLOAD_SIZE)
			write_str("type : tiny");
		else if (heap->min_block_payload_size == SMALL_BLOCK_MIN_PAYLOAD_SIZE)
			write_str("type : small");
		else if (heap->min_block_payload_size >= LARGE_BLOCK_MIN_PAYLOAD_SIZE)
			write_str("type : large");
		else
			write_str("type : ?");
		write_break();

		write_str("payload size : ");
		write_ulong(heap->total_payload_size, 10, false);
		write_break();

		write_str("start address : ");
		write_ptr(&heap->free_blocks);
		write_break();

		for (struct block_header *header = heap_get_begin(heap); heap_does_include_ptr(heap, header); header = block_get_next_header(block_get_footer_from_header(header)))
		{
			if (!header->is_allocated)
				continue;

			const void *payload = block_get_payload_from_header(header);

			write_str("-- BLOCK ----------------------------------------------------------------------");
			write_break();

			hex_dump(payload, header->payload_size);
			write_str("-------------------------------------------------------------------------------");
			write_break();
		}

		write_str("===============================================================================");
		write_break();
	}

	write_break();
}

void show_mem_debug(const char *message, t_bool show_allocated_blocks, t_bool show_free_blocks)
{
	if (message != NULL)
	{
		write_str(ANSI_BOLD);
		write_str(message);
		write_str(ANSI_RESET);
		write_break();
	}

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		write_ptr(heap);
		write_str(": total_size=");
		write_ulong(heap->total_payload_size, 10, false);
		write_str(", free_size=");
		write_ulong(heap->free_payload_size, 10, false);
		write_str(", free_blocks=");
		write_ptr(heap->free_blocks);
		write_break();

		for (struct block_header *header = heap_get_begin(heap); heap_does_include_ptr(heap, header); header = block_get_next_header(block_get_footer_from_header(header)))
		{
			const void *payload = block_get_payload_from_header(header);
			const void *footer = block_get_footer_from_header(header);

			if (!show_allocated_blocks && header->is_allocated)
				continue;
			if (!show_free_blocks && !header->is_allocated)
				continue;

			if (!header->is_allocated)
				write_str(ANSI_ITALIC);

			write_str("    ");
			write_ptr(header);

			write_str(": size=");
			write_ulong(footer - payload, 10, false);
			write_str(", is_allocated=");
			write_ulong(header->is_allocated, 10, false);
			if (!header->is_allocated)
			{
				write_str(", previous=");
				write_ptr(header->previous);
				write_str(", next=");
				write_ptr(header->next);
			}
			write_str(ANSI_RESET);
			write_break();
		}
	}

	write_break();
}

size_t get_total_available_memory()
{
	size_t total_available_memory = 0;

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		const size_t available_memory = heap_get_end(heap) - heap_get_begin(heap);
		total_available_memory += available_memory;
	}

	return total_available_memory;
}

size_t get_total_allocated_memory()
{
	size_t total_allocated_memory= 0;

	for (struct heap *heap = heaps; heap != NULL; heap = heap->next)
	{
		for (struct block_header *header = heap_get_begin(heap); heap_does_include_ptr(heap, header); header = block_get_next_header(block_get_footer_from_header(header)))
		{
			const void *payload = block_get_payload_from_header(header);
			const void *footer = block_get_footer_from_header(header);

			const size_t payload_size = footer - payload;

			if (header->is_allocated)
				total_allocated_memory += payload_size;
		}
	}

	return total_allocated_memory;
}