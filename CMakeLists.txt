cmake_minimum_required(VERSION 3.21)
project(malloc)

if (NOT TARGET ft)
	add_subdirectory(external/libft)
endif()

if (NOT TARGET ft_malloc)
	add_subdirectory(main)
endif()

add_subdirectory(test)