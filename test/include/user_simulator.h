#ifndef USER_SIMULATOR_H
#define USER_SIMULATOR_H

#include "malloc.h"

enum action
{
	action_allocate,
	action_reallocate,
	action_free,
	action_verify
};

struct allocation
{
	char *ptr;
	size_t length;
	struct allocation *previous;
	struct allocation *next;
};

struct user_simulator
{
	unsigned int seed;
	struct allocation *allocations_first;
	struct allocation *allocations_last;
	size_t allocations_count;
	t_bool logging;
	t_bool debugging;
	t_bool intermediate_state_validation;
	size_t allocation_max_size;
	size_t allocation_log_max_size;
	int allocation_frequency;
	int reallocation_frequency;
	int freeing_frequency;
	int verification_frequency;
};

void user_simulator_init(struct user_simulator *simulator);
void user_simulator_set_seed(struct user_simulator *simulator, unsigned int value);
void user_simulator_enable_logging(struct user_simulator *simulator);
void user_simulator_enable_debugging(struct user_simulator *simulator);
void user_simulator_enable_intermediate_state_validation(struct user_simulator *simulator);
void user_simulator_set_allocation_max_size(struct user_simulator *simulator, size_t value);
void user_simulator_set_allocation_log_max_size(struct user_simulator *simulator, size_t value);
void user_simulator_set_allocation_frequency(struct user_simulator *simulator, int value);
void user_simulator_set_reallocation_frequency(struct user_simulator *simulator, int value);
void user_simulator_set_freeing_frequency(struct user_simulator *simulator, int value);
void user_simulator_set_verification_frequency(struct user_simulator *simulator, int value);
t_bool user_simulator_execute_next();
void user_simulator_terminate(struct user_simulator *simulator);

#endif