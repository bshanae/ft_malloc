#include "utility_memory.h"

#include <unistd.h>

size_t get_allocation_limit()
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return -1;

	return rpl.rlim_max;
}

size_t get_page_size()
{
#ifdef FAKE_PAGE_SIZE
	return FAKE_PAGE_SIZE;
#endif

	return getpagesize();
}