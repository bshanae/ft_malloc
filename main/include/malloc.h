#ifndef MALLOC
#define MALLOC

#include <stdlib.h>
#include "heap.h"

#define TINY_BLOCK_MIN_PAYLOAD_SIZE 1
#define TINY_BLOCK_MAX_PAYLOAD_SIZE 64

#define SMALL_BLOCK_MIN_PAYLOAD_SIZE (TINY_BLOCK_MAX_PAYLOAD_SIZE + 1)
#define SMALL_BLOCK_MAX_PAYLOAD_SIZE 1024

#define LARGE_BLOCK_MIN_PAYLOAD_SIZE (SMALL_BLOCK_MAX_PAYLOAD_SIZE + 1)

#define BLOCKS_PER_HEAP 128

extern struct heap *g_heaps;
extern pthread_mutex_t g_mutex;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#endif
