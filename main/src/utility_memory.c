#include "utility_memory.h"

#include <unistd.h>

size_t get_allocation_limit()
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return -1;

	return rpl.rlim_max;
}