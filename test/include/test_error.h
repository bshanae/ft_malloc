#ifndef TEST_ERROR_H
#define TEST_ERROR_H

#include <limits.h>
#include "common.h"

#define START_ERROR_TEST(index) \
	void test_error_##index() \
	{ \
		const int _index = index;

#define FINISH_ERROR_TEST \
		validate_clean_state(); \
		write_str(ANSI_GREEN "Test error:"); \
		write_int(_index); \
		write_str(" passed." ANSI_RESET); \
		write_break(); \
	}

#define ASSERT(expression) \
    { \
        if (!(expression)) \
        { \
			write_str(ANSI_RED "Test error:"); \
			write_int(_index); \
			write_str(" failed." ANSI_RESET); \
			write_break(); \
			exit(1); \
        } \
    }

#define RUN_ERROR_TEST(index) \
	test_error_##index(); \

START_ERROR_TEST(1)
	void *ptr = malloc(0);
	ASSERT(ptr == NULL)
FINISH_ERROR_TEST

START_ERROR_TEST(2)
	void *ptr = malloc(ULONG_MAX);
	ASSERT(ptr == NULL)
FINISH_ERROR_TEST

START_ERROR_TEST(3)
	free(NULL);
FINISH_ERROR_TEST

START_ERROR_TEST(4)
	void *ptr0 = malloc(1);
	void *ptr1 = realloc(ptr0, 0);

	ASSERT(ptr1 == NULL)
	free(ptr0);
FINISH_ERROR_TEST

START_ERROR_TEST(5)
	void *ptr = realloc(NULL, 1);
	ASSERT(ptr != NULL)
	free(ptr);
FINISH_ERROR_TEST

t_bool test_error()
{
	RUN_ERROR_TEST(1)
	RUN_ERROR_TEST(2)
	RUN_ERROR_TEST(3)
	RUN_ERROR_TEST(4)
	RUN_ERROR_TEST(5)

	return true;
}

#endif
