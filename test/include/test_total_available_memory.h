#ifndef TEST_TOTAL_AVAILABLE_MEMORY_H
#define TEST_TOTAL_AVAILABLE_MEMORY_H

#include "common.h"

#define START_TOTAL_AVAILABLE_MEMORY_TEST(index) \
	void test_total_available_memory_##index() \
	{ \
		const int _index = index; \
		size_t _available_memory = 0; \
         \
		warm_up_heaps();


#define FINISH_TOTAL_AVAILABLE_MEMORY_TEST \
		validate_clean_state(); \
		write_str(ANSI_GREEN "Test available_memory:"); \
		write_int(_index); \
		write_str(" passed." ANSI_RESET); \
		write_break(); \
	}

#define SAVE_TOTAL_AVAILABLE_MEMORY \
	_available_memory = get_total_available_memory();

#define VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED \
    { \
        size_t current_available_memory = get_total_available_memory(); \
        if (current_available_memory != _available_memory) \
        { \
			write_str(ANSI_RED "Test available_memory:"); \
			write_int(_index); \
			write_str(" failed." ANSI_RESET); \
			write_break(); \
            printf(ANSI_RED "Was %lu, became %lu." ANSI_RESET, _available_memory, current_available_memory); \
			exit(1); \
        } \
    }

#define RUN_TOTAL_AVAILABLE_MEMORY_TEST(index) \
	test_total_available_memory_##index();

START_TOTAL_AVAILABLE_MEMORY_TEST(1)
	SAVE_TOTAL_AVAILABLE_MEMORY

	void *ptr0 = malloc(10);
	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED

	free(ptr0);
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

START_TOTAL_AVAILABLE_MEMORY_TEST(2)
	SAVE_TOTAL_AVAILABLE_MEMORY
	free(malloc(LARGE_BLOCK_MIN_PAYLOAD_SIZE)); // Allocate heap, then deallocate it.
	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

START_TOTAL_AVAILABLE_MEMORY_TEST(3)
	SAVE_TOTAL_AVAILABLE_MEMORY

	void *ptr0 = malloc(LARGE_BLOCK_MIN_PAYLOAD_SIZE);
	void *ptr1 = malloc(LARGE_BLOCK_MIN_PAYLOAD_SIZE);
	void *ptr2 = malloc(LARGE_BLOCK_MIN_PAYLOAD_SIZE);
	void *ptr3 = malloc(LARGE_BLOCK_MIN_PAYLOAD_SIZE);

	free(ptr0);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

START_TOTAL_AVAILABLE_MEMORY_TEST(4)
	SAVE_TOTAL_AVAILABLE_MEMORY

	const int test_size = 100;

	void *ptrs[test_size];

	for (int i = 0; i < test_size; i++)
		ptrs[i] = malloc(random_int_in_range(1000, 10000));
	for (int i = 0; i < test_size; i++)
		free(ptrs[i]);

	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

START_TOTAL_AVAILABLE_MEMORY_TEST(5)
	SAVE_TOTAL_AVAILABLE_MEMORY
	void *ptr = malloc(1);

	for (int i = 0; i < 10000; i++)
		ptr = realloc(ptr, 1 + i);

	free(ptr);
	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

START_TOTAL_AVAILABLE_MEMORY_TEST(6)
	SAVE_TOTAL_AVAILABLE_MEMORY
	void *ptr = malloc(1);

	for (int i = 0; i < 200000; i += 20)
		ptr = realloc(ptr, 1 + i);

	free(ptr);
	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

START_TOTAL_AVAILABLE_MEMORY_TEST(7)
	SAVE_TOTAL_AVAILABLE_MEMORY
	void *ptr = malloc(1);

	ptr = realloc(ptr, 1000);
	ptr = realloc(ptr, 10000);
	ptr = realloc(ptr, 100000);
	ptr = realloc(ptr, 1000000);

	free(ptr);
	VERIFY_TOTAL_AVAILABLE_MEMORY_DID_NOT_CHANGED
FINISH_TOTAL_AVAILABLE_MEMORY_TEST

t_bool test_total_available_memory()
{
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(1)
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(2)
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(3)
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(4)
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(5)
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(6)
	RUN_TOTAL_AVAILABLE_MEMORY_TEST(7)

	return true;
}

#endif
