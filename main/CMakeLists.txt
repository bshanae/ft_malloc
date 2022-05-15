cmake_minimum_required(VERSION 3.21)
project(ft_malloc)

if (NOT TARGET ft)
	add_subdirectory(../external/libft ${CMAKE_CURRENT_BINARY_DIR}/libft)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#if(DEFINED $ENV{HOST_TYPE})
#	set(HOST_TYPE $ENV{HOST_TYPE})
#else()
#	execute_process (
#	    COMMAND bash -c "echo $(uname -m)_$(uname -s)"
#		OUTPUT_VARIABLE HOST_TYPE
#	)
#endif()

add_library(ft_malloc SHARED
	src/block.c
	src/heap.c
	src/malloc.c
	src/malloc_debug.c
	src/utility_io.c
	src/utility_memory.c
)

target_include_directories(ft_malloc PRIVATE
	../external/libft/include
	include
)

target_link_libraries(ft_malloc ft)