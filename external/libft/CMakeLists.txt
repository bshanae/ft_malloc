cmake_minimum_required(VERSION 3.21)
project(ft)

add_library(ft STATIC
	#	STD NUM
	src/std_num/ft_max.c
	src/std_num/ft_min.c
	src/std_num/ft_abs.c
	#	STD CHAR
	src/std_char/is_space.c
	src/std_char/is_upper.c
	src/std_char/is_lower.c
	src/std_char/is_alpha.c
	src/std_char/is_dec.c
	src/std_char/to_upper.c
	src/std_char/to_lower.c
	src/std_char/is_hex.c
	src/std_char/is_integer.c
	src/std_char/is_float.c
	#	STD STR
	src/std_string/ft_strncat.c
	src/std_string/ft_strnstr.c
	src/std_string/ft_strlen.c
	src/std_string/ft_atof.c
	src/std_string/ft_strclr.c
	src/std_string/ft_strchr.c
	src/std_string/ft_strjoin.c
	src/std_string/ft_strstr.c
	src/std_string/ft_strcat.c
	src/std_string/ft_strdel.c
	src/std_string/ft_strrchr.c
	src/std_string/ft_strncmp.c
	src/std_string/ft_strcpy.c
	src/std_string/ft_strtrim.c
	src/std_string/ft_strnew.c
	src/std_string/ft_atoi_base.c
	src/std_string/ft_strdup.c
	src/std_string/ft_atoi.c
	src/std_string/ft_itoa.c
	src/std_string/ft_strsub.c
	src/std_string/ft_strncpy.c
	src/std_string/ft_strcmp.c
	src/std_string/ft_str_prefix.c
	src/std_string/ft_str_suffix.c
	src/std_string/ft_str_tokenize.c
	#	STD MEM
	src/std_mem/ft_memcmp.c
	src/std_mem/swap_memory.c
	src/std_mem/ft_bzero.c
	src/std_mem/ft_memcpy.c
	src/std_mem/ft_memalloc.c
	src/std_mem/ft_memccpy.c
	src/std_mem/ft_realloc.c
	src/std_mem/ft_memchr.c
	src/std_mem/ft_memset.c
	src/std_mem/ft_memdel.c
	src/std_mem/ft_memmove.c
	#	LIST2
	src/list2/list2_node_new.c
	src/list2/list2_node_delete.c
	src/list2/list2_node_connect.c
	src/list2/list2_create.c
	src/list2/list2_destroy.c
	src/list2/list2_push.c
	src/list2/list2_pop.c
	src/list2/list2_insert.c
	src/list2/list2_remove.c
	src/list2/list2_clear.c
)

target_include_directories(ft PRIVATE
	include)