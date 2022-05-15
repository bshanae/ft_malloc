#ifndef TEST_USER_H
#define TEST_USER_H

#include "common.h"
#include "user_simulator.h"

#define START_USER_TEST(index) \
	void test_random_##index() \
	{ \
		const int _index = index; \
		struct user_simulator _simulator; \
		user_simulator_init(&_simulator);

#define FINISH_USER_TEST \
		user_simulator_terminate(&_simulator); \
		validate_clean_state(); \
		write_str(ANSI_GREEN "Test random:"); \
		write_int(_index); \
		write_str(" passed." ANSI_RESET); \
		write_break(); \
	}

#define RUN_USER_TEST(index) \
	test_random_##index();

#define EXECUTE_SIMULATOR(count) \
	for (int i = 0; i < count; i++) \
	{ \
		if (!user_simulator_execute_next(&_simulator)) \
			exit(1); \
	}

START_USER_TEST(1)
	user_simulator_set_seed(&_simulator, 21);
	user_simulator_set_allocation_max_size(&_simulator, 10);
	user_simulator_set_allocation_frequency(&_simulator, 5);
	user_simulator_set_reallocation_frequency(&_simulator, 2);
	user_simulator_set_freeing_frequency(&_simulator, 8);
	user_simulator_set_verification_frequency(&_simulator, 6);
	user_simulator_enable_intermediate_state_validation(&_simulator);

	EXECUTE_SIMULATOR(10)
FINISH_USER_TEST

START_USER_TEST(2)
	user_simulator_set_seed(&_simulator, 21);
	user_simulator_set_allocation_max_size(&_simulator, 1000);
	user_simulator_set_allocation_frequency(&_simulator, 5);
	user_simulator_set_reallocation_frequency(&_simulator, 2);
	user_simulator_set_freeing_frequency(&_simulator, 8);
	user_simulator_set_verification_frequency(&_simulator, 6);
	user_simulator_enable_intermediate_state_validation(&_simulator);

	EXECUTE_SIMULATOR(100)
FINISH_USER_TEST

START_USER_TEST(3)
	user_simulator_set_seed(&_simulator, 21);
	user_simulator_set_allocation_max_size(&_simulator, 1000);
	user_simulator_set_allocation_frequency(&_simulator, 5);
	user_simulator_set_reallocation_frequency(&_simulator, 2);
	user_simulator_set_freeing_frequency(&_simulator, 8);
	user_simulator_set_verification_frequency(&_simulator, 6);
	user_simulator_enable_intermediate_state_validation(&_simulator);

	EXECUTE_SIMULATOR(100000)
FINISH_USER_TEST

START_USER_TEST(4)
	user_simulator_set_seed(&_simulator, 21);
	user_simulator_set_allocation_max_size(&_simulator, 1000);
	user_simulator_set_allocation_frequency(&_simulator, 5);
	user_simulator_set_reallocation_frequency(&_simulator, 2);
	user_simulator_set_freeing_frequency(&_simulator, 4);
	user_simulator_set_verification_frequency(&_simulator, 6);
	user_simulator_enable_intermediate_state_validation(&_simulator);

	EXECUTE_SIMULATOR(10000)
FINISH_USER_TEST

START_USER_TEST(5)
	user_simulator_set_seed(&_simulator, 22);
	user_simulator_set_allocation_max_size(&_simulator, 1000);
	user_simulator_set_allocation_frequency(&_simulator, 5);
	user_simulator_set_reallocation_frequency(&_simulator, 2);
	user_simulator_set_freeing_frequency(&_simulator, 8);
	user_simulator_set_verification_frequency(&_simulator, 6);
	user_simulator_enable_intermediate_state_validation(&_simulator);

	EXECUTE_SIMULATOR(100000)
FINISH_USER_TEST

START_USER_TEST(6)
	user_simulator_set_seed(&_simulator, 21);
	user_simulator_set_allocation_max_size(&_simulator, 100000);
	user_simulator_set_allocation_frequency(&_simulator, 5);
	user_simulator_set_reallocation_frequency(&_simulator, 2);
	user_simulator_set_freeing_frequency(&_simulator, 8);
	user_simulator_set_verification_frequency(&_simulator, 6);
	user_simulator_enable_intermediate_state_validation(&_simulator);

	EXECUTE_SIMULATOR(100)
FINISH_USER_TEST

void test_user()
{
	RUN_USER_TEST(1)
	RUN_USER_TEST(2)
	RUN_USER_TEST(3)
	RUN_USER_TEST(4)
	RUN_USER_TEST(5)
	RUN_USER_TEST(6)
}

#endif