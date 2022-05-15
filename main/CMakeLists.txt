cmake_minimum_required(VERSION 3.21)
project(ft_malloc)

if (NOT TARGET ft)
	add_subdirectory(../external/libft ${CMAKE_CURRENT_BINARY_DIR}/libft)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra -fPIC")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/..)

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

set_target_properties(ft_malloc PROPERTIES SUFFIX ".so")

add_custom_command(TARGET ft_malloc
	POST_BUILD
    COMMAND bash main/create_link.sh
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/.."
	COMMENT "Creating symbolic link to the library"
)