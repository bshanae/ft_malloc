/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:15:36 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:43:00 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STANDART_H
# define LIBFT_STANDART_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum		e_bool
{
	false,
	true
}					t_bool;

# define VOID_REF	const void *

# define INT_REF	const int *
# define UINT_REF	const unsigned int *
# define UINT		unsigned int

# define CHAR_REF	const char *
# define UCHAR_REF	const unsigned char *
# define UCHAR		unsigned char

# define LONG_REF	const long *
# define ULONG_REF	const unsigned long *
# define ULONG		unsigned long

void				*ft_memset(void *str, int c, size_t n);
void				*ft_memcpy(void *str1, const void *str2, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *str, int value, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				ft_bzero(void *str, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_realloc(void **m, size_t old_size, size_t new_size);
void				swap_memory(void *a, void *b, size_t size);

int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					ft_abs(int a);

int					is_upper(const char *c);
int					is_lower(const char *c);
int					is_alpha(const char *c);
void				to_lower(char *c);
void				to_upper(char *c);
int					is_dec(const char *c);
int					is_hex(const char *c);
int					is_space(const char *c);
int					is_integer(const char *c);
int					is_float(const char *c);

int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int base);
double				ft_atof(const char *str, int *length);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *str);
char				*ft_strdup (const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *str, int value);
char				*ft_strrchr(const char *str, int value);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);

int					ft_atoi_rigorous(const char *str);
char				**ft_str_tokenize(const char *string, char delimiter, t_bool save_delimiter);
int					ft_str_prefix(const char *string, const char *prefix);
int					ft_str_suffix(const char *string, const char *suffix);

#endif
