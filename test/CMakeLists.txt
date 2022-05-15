cmake_minimum_required(VERSION 3.21)
project(ft_malloc_test)

if (NOT TARGET ft)
	add_subdirectory(../external/libft ${CMAKE_CURRENT_BINARY_DIR}/libft)
endif()

if (NOT TARGET ft_malloc)
	add_subdirectory(../main ${CMAKE_CURRENT_BINARY_DIR}/malloc)
endif()

add_executable(ft_malloc_test
	src/main.c
	src/user_simulator.c)

target_include_directories(ft_malloc_test PRIVATE
	../external/libft/include
	../main/include
	include)

target_link_libraries(ft_malloc_test
	ft
	ft_malloc)