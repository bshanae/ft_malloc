#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "common.h"

#define START_DATA_TEST(index) \
	void test_data_##index() \
	{ \
	    const int _index = index;

#define FINISH_DATA_TEST \
        validate_clean_state(); \
        write_str(ANSI_GREEN "Test data:"); \
        write_int(_index); \
        write_str(" passed." ANSI_RESET); \
        write_break(); \
    }

#define VERIFY_STRING(ptr, expected) \
    if (ft_strcmp(ptr, expected)) \
    { \
        write_str(ANSI_RED "Test data:"); \
        write_int(_index); \
        write_str(" failed." ANSI_RESET); \
        write_break(); \
        printf(ANSI_RED "Expected '%s', got '%s'." ANSI_RESET, expected, ptr); \
		exit(1); \
    }

#define VERIFY_CHAR(ptr, size, expected) \
    for (int _i = 0; _i < size; _i++) \
    { \
        if (ptr[_i] != expected) \
        { \
            write_str(ANSI_RED "Test data:"); \
            write_int(_index); \
            write_str(" failed." ANSI_RESET); \
            write_break(); \
            printf(ANSI_RED "Expected '%c', got '%c'." ANSI_RESET, expected, ptr[_i]); \
			exit(1); \
        } \
    } \

#define RUN_DATA_TEST(index) \
	test_data_##index();


START_DATA_TEST(1)
	const char str[] = "hello there";
	char *ptr = malloc(16);

	ft_strcpy(ptr, str);
	litter_heaps();

	VERIFY_STRING(ptr, str)
	free(ptr);
FINISH_DATA_TEST

START_DATA_TEST(2)
	const char str[] = "hello there";

	char *ptr1 = malloc(16);
	char *ptr2 = malloc(16);

	ft_strcpy(ptr1, str);
	ft_strcpy(ptr2, str);

	litter_heaps();

	VERIFY_STRING(ptr1, str)
	VERIFY_STRING(ptr1, str)

	free(ptr1);
	free(ptr2);
FINISH_DATA_TEST

START_DATA_TEST(3)
	const char str1[] = "hello";
	const char str2[] = "there";

	char *ptr1 = malloc(16);
	ft_strcpy(ptr1, str1);
	free(ptr1);

	char *ptr2 = malloc(16);
	ft_strcpy(ptr2, str2);
	free(ptr2);

	VERIFY_STRING(ptr2, str2)
FINISH_DATA_TEST

START_DATA_TEST(4)
	const char str[] = "hello there";

	for (int i = 0; i < 1000000; i++)
	{
		char *ptr0 = malloc(16);

		ft_strcpy(ptr0, str);
		VERIFY_STRING(ptr0, str)

		free(ptr0);
	}
FINISH_DATA_TEST

START_DATA_TEST(5)
	const char str[] = "hello there";

	for (int i = 0; i < 1000000; i++)
	{
		char *ptr0 = malloc(16);

		ft_strcpy(ptr0, str);
		VERIFY_STRING(ptr0, str)

		free(ptr0);
	}
FINISH_DATA_TEST

START_DATA_TEST(6)
	const int test_size = 10000;
	const char test_str[] = "abcdefghijklmno";

	char *ptrs[test_size];

	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = malloc(16);
		ft_strcpy(ptrs[i], test_str);
	}

	litter_heaps();

	for (int i = 0; i < test_size; i++)
	{
		VERIFY_STRING(ptrs[i], test_str)
	}

	for (int i = 0; i < test_size; i++)
	{
		free(ptrs[i]);
	}
FINISH_DATA_TEST

START_DATA_TEST(7)
	const int test_size = 10000;
	const char test_str1[] = "abcdefghijklmno";
	const char test_str2[] = "onmlkjihgfedcba";

	char *ptrs[test_size];

	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = malloc(16);
		ft_strcpy(ptrs[i], test_str1);
	}

	for (int i = 0; i < test_size; i++)
		free(ptrs[i]);

	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = malloc(16);
		ft_strcpy(ptrs[i], test_str2);
	}

	litter_heaps();

	for (int i = 0; i < test_size; i++)
		VERIFY_STRING(ptrs[i], test_str2)

	for (int i = 0; i < test_size; i++)
		free(ptrs[i]);
FINISH_DATA_TEST

START_DATA_TEST(8)
	const int test_size = 1000;
	const char test_char = 'e';

	char *ptrs[test_size];
	int sizes[test_size];

	for (int i = 0; i < test_size; i++)
	{
		sizes[i] = random_int_in_range(1, 10000);
		ptrs[i] = malloc(sizes[i]);
		ft_memset(ptrs[i], test_char, sizes[i]);
	}

	litter_heaps();

	for (int i = 0; i < test_size; i++)
		VERIFY_CHAR(ptrs[i], sizes[i], test_char);
	for (int i = 0; i < test_size; i++)
		free(ptrs[i]);
FINISH_DATA_TEST

START_DATA_TEST(9)
	const char test_str1[] = "abcde";
	const char test_str2[] = "onmlkjihgf";

	char *ptr = malloc(6);
	ft_strcpy(ptr, test_str1);

	litter_heaps();

	ptr = realloc(ptr, 11);
	ft_strcpy(ptr, test_str2);

	litter_heaps();

	VERIFY_STRING(ptr, test_str2);

	free(ptr);
FINISH_DATA_TEST

START_DATA_TEST(10)
	const int test_size = 10000;
	const char test_str1[] = "abcde";
	const char test_str2[] = "onmlkjihgf";

	char *ptrs[test_size];

	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = malloc(6);
		ft_strcpy(ptrs[i], test_str1);
	}
	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = realloc(ptrs[i], 11);
		ft_strcpy(ptrs[i], test_str2);
	}

	for (int i = 0; i < test_size; i++)
	{
		VERIFY_STRING(ptrs[i], test_str2)
	}

	for (int i = 0; i < test_size; i++)
	{
		free(ptrs[i]);
	}
FINISH_DATA_TEST

START_DATA_TEST(11)
	const int test_size = 1000;
	const char test_char_1 = 'a';
	const char test_char_2 = 'b';

	char *ptrs[test_size];
	int sizes[test_size];

	for (int i = 0; i < test_size; i++)
	{
		sizes[i] = random_int_in_range(1, 10000);
		ptrs[i] = malloc(sizes[i]);
		ft_memset(ptrs[i], test_char_1, sizes[i]);
	}
	for (int i = 0; i < test_size; i++)
	{
		sizes[i] = random_int_in_range(1, 10000);
		ptrs[i] = realloc(ptrs[i], sizes[i]);
		ft_memset(ptrs[i], test_char_2, sizes[i]);
	}
	for (int i = 0; i < test_size; i++)
	{
		VERIFY_CHAR(ptrs[i], sizes[i], test_char_2);
	}
	for (int i = 0; i < test_size; i++)
	{
		free(ptrs[i]);
	}
FINISH_DATA_TEST

t_bool test_data()
{
	RUN_DATA_TEST(1)
	RUN_DATA_TEST(2)
	RUN_DATA_TEST(3)
	RUN_DATA_TEST(4)
	RUN_DATA_TEST(5)
	RUN_DATA_TEST(6)
	RUN_DATA_TEST(7)
	RUN_DATA_TEST(8)
	RUN_DATA_TEST(9)
	RUN_DATA_TEST(10)
	RUN_DATA_TEST(11)

	return true;
}

#endif
