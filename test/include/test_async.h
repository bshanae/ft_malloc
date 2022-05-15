#ifndef TEST_ASYNC_H
#define TEST_ASYNC_H

#include <limits.h>
#include <pthread.h>
#include "common.h"

#define START_ASYNC_TEST(id) \
	void *test_async_##id(void *thread_id) \
	{ \
		const char *_id = STR(id);

#define FINISH_ASYNC_TEST \
		pthread_exit(NULL); \
        return NULL; \
	}

#define RUN_ASYNC_TEST(id) \
    run_async_test(STR(id), &test_async_##id);

void run_async_test(const char *id, void *(*test)(void *))
{
	const int number_of_thread = 4;

	pthread_t threads[number_of_thread];

	for (long i = 0; i < number_of_thread; i++)
	{
		int return_code = pthread_create(&threads[i], NULL, test, (void *)i);
		if (return_code)
		{
			printf("Can't create thread, return code: %d\n", return_code);
			exit(1);
		}
	}

	sleep(1);

	for (long i = 0; i < number_of_thread; i++)
	{
		pthread_join(threads[i], NULL);
	}

	write_str(ANSI_GREEN "Test async:"); \
	write_str(id); \
	write_str(" passed." ANSI_RESET); \
	write_break(); \
	validate_clean_state();
}

START_ASYNC_TEST(allocate_memory_verify_free)
	const int test_size = 100;
	const char *data = "hello there";

	void *ptrs[100] = {};
	size_t data_size = ft_strlen(data);

	for (int i = 0; i < test_size; i++)
	{
		ptrs[i] = malloc(data_size + 1);
		ft_strcpy(ptrs[i], data);
	}

	for (int i = 0; i < test_size; i++)
	{
		if (ft_strcmp(ptrs[i], data))
			exit(1);
	}

	for (int i = 0; i < test_size; i++)
	{
		free(ptrs[i]);
	}
FINISH_ASYNC_TEST

void test_async()
{
	RUN_ASYNC_TEST(allocate_memory_verify_free)
}

#endif
