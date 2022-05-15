#ifndef TEST_TOTAL_ALLOCATED_MEMORY_H
#define TEST_TOTAL_ALLOCATED_MEMORY_H

#include "common.h"

#define START_TOTAL_ALLOCATED_MEMORY_TEST(index) \
	void test_total_allocated_memory_##index() \
	{ \
		const int _index = index;

#define FINISH_TOTAL_ALLOCATED_MEMORY_TEST \
		validate_clean_state(); \
		write_str(ANSI_GREEN "Test allocated_memory:"); \
		write_int(_index); \
		write_str(" passed." ANSI_RESET); \
		write_break(); \
	}

#define VERIFY_TOTAL_ALLOCATED_MEMORY(expected_size) \
    { \
        size_t actual_size = get_total_allocated_memory(); \
        if (actual_size != (expected_size)) \
        { \
			write_str(ANSI_RED "Test allocated_memory:"); \
			write_int(_index); \
			write_str(" failed." ANSI_RESET); \
			write_break(); \
            printf(ANSI_RED "Expected %lu, got %lu." ANSI_RESET, expected_size, actual_size); \
			exit(1); \
        } \
    }

#define RUN_TOTAL_ALLOCATED_MEMORY_TEST(index) \
	test_total_allocated_memory_##index();

START_TOTAL_ALLOCATED_MEMORY_TEST(1)
	void *ptr0 = malloc(1);

	VERIFY_TOTAL_ALLOCATED_MEMORY(1lu)

	free(ptr0);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(2)
	void *ptr0 = malloc(4);

	VERIFY_TOTAL_ALLOCATED_MEMORY(4lu)

	free(ptr0);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(3)
	void *ptr0 = malloc(10);

	VERIFY_TOTAL_ALLOCATED_MEMORY(10lu)

	free(ptr0);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(4)
	void *ptr0 = malloc(10);
	void *ptr1 = malloc(10);

	VERIFY_TOTAL_ALLOCATED_MEMORY(20lu)

	free(ptr0);
	free(ptr1);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(5)
	free(malloc(10));
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(6)
	void *ptr0 = malloc(10);
	void *ptr1 = malloc(10);

	VERIFY_TOTAL_ALLOCATED_MEMORY(20lu)

	free(ptr0);
	free(ptr1);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(7)
	void *ptr0 = malloc(100000);
	void *ptr1 = malloc(100000);

	VERIFY_TOTAL_ALLOCATED_MEMORY(200000lu)

	free(ptr0);
	free(ptr1);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(8)
	void *ptr0 = malloc(10);
	void *ptr1 = malloc(10);
	void *ptr2 = malloc(10);
	void *ptr3 = malloc(10);
	void *ptr4 = malloc(10);
	void *ptr5 = malloc(10);
	void *ptr6 = malloc(10);
	void *ptr7 = malloc(10);
	void *ptr8 = malloc(10);
	void *ptr9 = malloc(10);

	VERIFY_TOTAL_ALLOCATED_MEMORY(100lu)

	free(ptr0);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	free(ptr6);
	free(ptr7);
	free(ptr8);
	free(ptr9);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(9)
	for (int i = 0; i < 100000; i++)
		free(malloc(10));

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(10)
	void *ptr0 = malloc(10);
	void *ptr1 = malloc(10);
	void *ptr2 = malloc(10);
	void *ptr3 = malloc(10);
	void *ptr4 = malloc(10);
	void *ptr5 = malloc(10);
	void *ptr6 = malloc(10);
	void *ptr8 = malloc(10);
	void *ptr9 = malloc(10);

	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	free(ptr6);
	free(ptr8);
	free(ptr9);

	VERIFY_TOTAL_ALLOCATED_MEMORY(10lu)

	free(ptr0);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(11)
	void *ptr0 = malloc(1);
	void *ptr1 = malloc(1);
	void *ptr2 = malloc(1);
	void *ptr3 = malloc(1);
	void *ptr4 = malloc(1);
	void *ptr5 = malloc(1);
	void *ptr6 = malloc(1);
	void *ptr7 = malloc(1);
	void *ptr8 = malloc(1);
	void *ptr9 = malloc(1);

	free(ptr0);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	free(ptr6);
	free(ptr7);
	free(ptr8);
	free(ptr9);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(12)
	void *ptr0 = malloc(1);
	void *ptr1 = malloc(4);
	void *ptr2 = malloc(16);
	void *ptr3 = malloc(64);
	void *ptr4 = malloc(256);
	void *ptr5 = malloc(1024);
	void *ptr6 = malloc(4096);
	void *ptr7 = malloc(16384);
	void *ptr8 = malloc(65536);
	void *ptr9 = malloc(262144);

	free(ptr0);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	free(ptr6);
	free(ptr7);
	free(ptr8);
	free(ptr9);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(13)
	void *ptr = malloc(10);
	VERIFY_TOTAL_ALLOCATED_MEMORY(10lu)

	ptr = realloc(ptr, 11);
	VERIFY_TOTAL_ALLOCATED_MEMORY(11lu)

	free(ptr);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(14)
	void *ptr = malloc(1000);
	VERIFY_TOTAL_ALLOCATED_MEMORY(1000lu)

	ptr = realloc(ptr, 16000);
	VERIFY_TOTAL_ALLOCATED_MEMORY(16000lu)

	free(ptr);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(15)
	void *ptr = malloc(1);
	VERIFY_TOTAL_ALLOCATED_MEMORY(1lu)

	for (int i = 0; i < 1000; i++)
	{
		ptr = realloc(ptr, 1 + i);
		VERIFY_TOTAL_ALLOCATED_MEMORY(1lu + i)
	}

	free(ptr);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(16)
	const int test_size = 100;
	const int initial_size = 100;
	const int realloc_multiplier = 100;

	void *ptrs[100];

	for (int i = 0; i < test_size; i++)
		ptrs[i] = malloc(initial_size);

	size_t total_realloc_size = 0;
	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = realloc(ptrs[i], realloc_multiplier * (i + 1));
		total_realloc_size += realloc_multiplier * (i + 1);
	}

	VERIFY_TOTAL_ALLOCATED_MEMORY(total_realloc_size)

	for (int i = 0; i < test_size; i++)
		free(ptrs[i]);

	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(17)
	void *ptr = malloc(1000);
	VERIFY_TOTAL_ALLOCATED_MEMORY(1000lu)

	ptr = realloc(ptr, 100);
	VERIFY_TOTAL_ALLOCATED_MEMORY(100lu)

	ptr = realloc(ptr, 10);
	VERIFY_TOTAL_ALLOCATED_MEMORY(10lu)

	ptr = realloc(ptr, 1);
	VERIFY_TOTAL_ALLOCATED_MEMORY(1lu)

	free(ptr);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(18)
	void *ptr = malloc(1);

	for (int i = 0; i < 10000; i++)
	{
		size_t new_size = random_int_in_range(1, 1000000);

		ptr = realloc(ptr, new_size);
		VERIFY_TOTAL_ALLOCATED_MEMORY(new_size)
	}

	free(ptr);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

START_TOTAL_ALLOCATED_MEMORY_TEST(19)
	void *ptr = malloc(1000);
	ptr = realloc(ptr, 10);

	VERIFY_TOTAL_ALLOCATED_MEMORY(10lu)

	free(ptr);
	VERIFY_TOTAL_ALLOCATED_MEMORY(0lu)
FINISH_TOTAL_ALLOCATED_MEMORY_TEST

t_bool test_total_allocated_memory()
{
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(1)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(2)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(3)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(4)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(5)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(6)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(7)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(8)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(9)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(10)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(11)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(12)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(13)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(14)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(15)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(16)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(17)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(18)
	RUN_TOTAL_ALLOCATED_MEMORY_TEST(19)

	return true;
}

#endif
