#ifndef MALLOC_DEBUG
#define MALLOC_DEBUG

#include "malloc.h"

#define ANSI_BOLD    "\e[1m"
#define ANSI_ITALIC  "\e[3m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_RESET   "\x1b[0m"

void show_alloc_mem();
void show_alloc_mem_ex(const char *message);
void show_mem_debug(const char *message, t_bool show_allocated_blocks, t_bool show_free_blocks);

size_t get_total_available_memory();
size_t get_total_allocated_memory();

#endif
