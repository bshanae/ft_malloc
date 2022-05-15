/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:15:25 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:57:58 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_VECTOR_H
# define LIBFT_VECTOR_H

# include "libft_standart.h"
# include "libft_error.h"

# define VECTOR_ALLOC_INIT	10
# define VECTOR_ALLOC_MULT	2
# define VECTOR_ALLOC_LIMIT	0.5
# define VECTOR_RESIZE_MULT 1.5

typedef void				(*t_vector_f1)(void *, void *);
typedef int					(*t_vector_f2)(VOID_REF, VOID_REF);

typedef struct				s_vector
{
	void					*storage;
	size_t					element_size;
	size_t					capacity;
	size_t					length;
}							t_vector;

typedef struct				s_vector_iter
{
	t_vector				*vector;
	size_t					index;
}							t_vector_iter;

t_vector					*vector_create(size_t element_size);
void						vector_destroy(t_vector **me);

void						vector_realloc(
	t_vector *me, size_t capacity, t_bool save_data);

void						*vector_at(t_vector *me, int index);
size_t						vector_index(t_vector *me, void *ptr);

t_vector_iter				vector_push(t_vector *me, void *data);
void						vector_pop(t_vector *me);
void						vector_insert(t_vector *me, size_t i, void *data);
void						vector_erase(t_vector *me, size_t index);

void						*vector_front(t_vector *me);
void						*vector_back(t_vector *me);

void						vector_resize(
	t_vector *me, size_t count, void *data);
void						vector_clear(t_vector *me);
void						vector_set(
	t_vector *me, size_t begin, size_t end, void *data);

void						vector_print(
	t_vector *me, t_vector_f1 f, void *ptr);
void						vector_foreach(
	t_vector *me, t_vector_f1 f, void *ptr);

void						*vector_find(
	t_vector *me, t_vector_f2 cmp, VOID_REF ptr);

t_vector_iter				vector_iter_set(t_vector *vector, size_t index);
void						*vector_iter_ptr(t_vector_iter *iter);
int							vector_iter_next(t_vector_iter *iter);
int							vector_iter_previous(t_vector_iter *iter);

t_bool						vector_copy(
	t_vector *destination, t_vector *source);

#endif
