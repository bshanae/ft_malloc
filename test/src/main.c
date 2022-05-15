#include "test_error.h"
#include "test_total_available_memory.h"
#include "test_total_allocated_memory.h"
#include "test_data.h"
#include "test_user.h"

int main()
{
	test_error();
	test_total_available_memory();
	test_total_allocated_memory();
	test_data();
	test_user();
}