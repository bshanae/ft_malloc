#include "user_simulator.h"

#include "utility_io.h"
#include "utility.h"
#include "malloc_debug.h"
#include "common.h"

// INTERNAL : UTILITIES ----------------------------------------------------------------------------------------------------------------------------------------

static char get_char_at_index(int index)
{
	return (char)((index % 'z') + 'a');
}

static void start_message(struct user_simulator *simulator)
{
	if (simulator->debugging)
		write_str(ANSI_BOLD);

	write_str("-------------------------------------------------------------------------------------------------------");
}

static void finish_message(struct user_simulator *simulator)
{
	if (simulator->debugging)
		write_str(ANSI_RESET);
}

// INTERNAL : RANDOM -------------------------------------------------------------------------------------------------------------------------------------------

static int get_random_int(struct user_simulator *simulator, int min, int max)
{
    unsigned int r = simulator->seed;

    r ^= r << 13;
    r ^= r >> 17;
    r ^= r << 5;
	simulator->seed = r;

	const int result = (int)(r & 2147483647);
	return result % (max - min) + min;
}

static enum action get_next_action(struct user_simulator *simulator)
{
	return get_random_int(simulator, action_allocate, action_verify + 1);
}

static struct allocation *get_random_allocation(struct user_simulator *simulator)
{
	if (simulator->allocations_count == 0)
		return NULL;

	const int target_i = get_random_int(simulator, 0, (int)simulator->allocations_count);

	struct allocation *node = simulator->allocations_first;
	for (int i = 0; i < target_i; i++)
		node = node->next;

	return node;
}

// INTERNAL : ALLOCATION ---------------------------------------------------------------------------------------------------------------------------------------

static void allocation_initialize(struct allocation *allocation, size_t data_size)
{
	allocation->ptr = malloc(data_size);
	allocation->length = data_size;
	allocation->previous = NULL;
	allocation->next = NULL;
}

static void allocation_deinitialize(struct allocation *allocation)
{
	free(allocation->ptr);
	allocation->length = 0;
	allocation->previous = NULL;
	allocation->next = NULL;
}

static void allocation_remove(struct allocation *target, struct allocation **first, struct allocation **last, size_t *count)
{
	(*count)--;

	if (target == *first)
		*first = target->next;
	if (target == *last)
		*last = target->previous;

	if (target->previous != NULL)
		target->previous->next = target->next;
	if (target->next != NULL)
		target->next->previous = target->previous;

	allocation_deinitialize(target);
	free(target);
}

static void allocation_push(struct allocation *new, struct allocation **first, struct allocation **last, size_t *count)
{
	(*count)++;

	if (*first == NULL)
	{
		*first = new;
	}
	else
	{
		(*last)->next = new;
		new->previous = *last;
	}

	*last = new;
}

static void allocation_clear(struct allocation **first, struct allocation **last, size_t *count)
{
	struct allocation *iterator = *first;
	while (iterator != NULL)
	{
		struct allocation *target = iterator;
		iterator = iterator->next;

		allocation_deinitialize(target);
		free(target);
	}

	*first = NULL;
	*last = NULL;
	*count = 0;
}

static void fill_allocation(struct allocation *allocation)
{
	for (int i = 0; i < allocation->length; i++)
		allocation->ptr[i] = get_char_at_index(i);
}

static t_bool verify_allocation(struct allocation *allocation)
{
	for (int i = 0; i < allocation->length; i++)
	{
		if (allocation->ptr[i] != get_char_at_index(i))
			return false;
	}

	return true;
}

// INTERNAL : ACTIONS ------------------------------------------------------------------------------------------------------------------------------------------

static t_bool perform_allocation(struct user_simulator *simulator)
{
	const int length = get_random_int(simulator, 1, (int)simulator->allocation_max_size);

	struct allocation *allocation = malloc(sizeof(struct allocation));
	allocation_initialize(allocation, length);
	fill_allocation(allocation);

	allocation_push(allocation, &simulator->allocations_first, &simulator->allocations_last, &simulator->allocations_count);

	if (simulator->logging)
	{
		start_message(simulator);
		write_str("Allocation: ptr=");
		write_ptr(allocation->ptr);
		write_str(", size=");
		write_int(length);
		write_break();
		finish_message(simulator);
	}

	return true;
}

static t_bool perform_reallocation(struct user_simulator *simulator)
{
	struct allocation *allocation = get_random_allocation(simulator);
	if (allocation == NULL)
	{
		if (simulator->logging)
		{
			start_message(simulator);
			write_str("Reallocation failed, no available allocation found.");
			write_break();
			finish_message(simulator);
		}

		return true;
	}

	const int length = get_random_int(simulator, 1, 10000);

	allocation->length = length;
	allocation->ptr = realloc(allocation->ptr, length);

	fill_allocation(allocation);

	if (simulator->logging)
	{
		start_message(simulator);
		write_str("Reallocation: ptr=");
		write_ptr(allocation->ptr);
		write_str(", old_size=");
		write_ulong(allocation->length, 10, false);
		write_str(", new_size=");
		write_int(length);
		write_break();
		finish_message(simulator);
	}

	return true;
}

static t_bool perform_freeing(struct user_simulator *simulator)
{
	struct allocation *allocation = get_random_allocation(simulator);
	if (allocation == NULL)
	{
		if (simulator->logging)
		{
			start_message(simulator);
			write_str("Freeing failed, no available allocation found.");
			write_break();
			finish_message(simulator);
		}

		return true;
	}

	if (simulator->logging)
	{
		start_message(simulator);
		write_str("Freeing: ptr=");
		write_ptr(allocation->ptr);
		write_str(", size=");
		write_ulong(allocation->length, 10, false);
		write_break();
		finish_message(simulator);
	}

	allocation_remove(allocation, &simulator->allocations_first, &simulator->allocations_last, &simulator->allocations_count);

	return true;
}

static t_bool perform_verification(struct user_simulator *simulator)
{
	struct allocation *allocation = get_random_allocation(simulator);
	if (allocation == NULL)
	{
		if (simulator->logging)
		{
			start_message(simulator);
			write_str("Verification failed, no available allocation found.");
			write_break();
			finish_message(simulator);
		}

		return true;
	}

	if (simulator->logging)
	{
		start_message(simulator);
		write_str("Verification: size=");
		write_ulong(allocation->length, 10, false);
		write_str(", data=");
		write_str_unterminated(allocation->ptr, MIN(allocation->length, simulator->allocation_log_max_size));
		if (allocation->length > simulator->allocation_log_max_size)
			write_str("...");
		write_break();
		finish_message(simulator);
	}

	return verify_allocation(allocation);
}

// API ---------------------------------------------------------------------------------------------------------------------------------------------------------

void user_simulator_init(struct user_simulator *simulator)
{
	simulator->seed = 42;
	simulator->allocations_first = NULL;
	simulator->allocations_last = NULL;
	simulator->allocations_count = 0;
	simulator->logging = false;
	simulator->debugging = false;
	simulator->intermediate_state_validation = false;
	simulator->allocation_max_size = 1000;
	simulator->allocation_log_max_size = 20;
	simulator->allocation_frequency = 1;
	simulator->reallocation_frequency = 1;
	simulator->freeing_frequency = 1;
	simulator->verification_frequency = 1;
}

void user_simulator_set_seed(struct user_simulator *simulator, unsigned int value)
{
	simulator->seed = value;
}

void user_simulator_enable_logging(struct user_simulator *simulator)
{
	simulator->logging = true;
}

void user_simulator_enable_debugging(struct user_simulator *simulator)
{
	simulator->debugging = true;
}

void user_simulator_enable_intermediate_state_validation(struct user_simulator *simulator)
{
	simulator->intermediate_state_validation = true;
}

void user_simulator_set_allocation_max_size(struct user_simulator *simulator, size_t value)
{
	simulator->allocation_max_size = value;
}

void user_simulator_set_allocation_log_max_size(struct user_simulator *simulator, size_t value)
{
	simulator->allocation_log_max_size = value;
}

void user_simulator_set_allocation_frequency(struct user_simulator *simulator, int value)
{
	simulator->allocation_frequency = value;
}

void user_simulator_set_reallocation_frequency(struct user_simulator *simulator, int value)
{
	simulator->reallocation_frequency = value;
}

void user_simulator_set_freeing_frequency(struct user_simulator *simulator, int value)
{
	simulator->freeing_frequency = value;
}

void user_simulator_set_verification_frequency(struct user_simulator *simulator, int value)
{
	simulator->verification_frequency = value;
}

t_bool user_simulator_execute_next(struct user_simulator *simulator)
{
	int repeat_max = 0;
	t_bool (* action)(struct user_simulator *simulator) = 0;

	switch (get_next_action(simulator))
	{
		case action_allocate:
			repeat_max = simulator->allocation_frequency;
			action = &perform_allocation;
			break;

		case action_reallocate:
			repeat_max = simulator->reallocation_frequency;
			action = &perform_reallocation;
			break;

		case action_free:
			repeat_max = simulator->freeing_frequency;
			action = &perform_freeing;
			break;

		case action_verify:
			repeat_max = simulator->verification_frequency;
			action = &perform_verification;
			break;
	}

	const int repeat_count = get_random_int(simulator, 0, repeat_max + 1);
	for (int i = 0; i < repeat_count; i++)
	{
		if (!action(simulator))
			return false;

		if (simulator->debugging)
			show_mem_debug(NULL, false, true);

		if (simulator->intermediate_state_validation)
			validate_intermediate_state();
	}

	return true;
}

void user_simulator_terminate(struct user_simulator *simulator)
{
	allocation_clear(&simulator->allocations_first, &simulator->allocations_last, &simulator->allocations_count);
}