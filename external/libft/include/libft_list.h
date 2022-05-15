/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:16:38 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:43:05 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include "libft_standart.h"
# include "libft_error.h"

typedef struct			s_list_item
{
	void				*data;
	struct s_list_item	*next;
}						t_list_item;

t_list_item				*list_item_new(VOID_REF data, size_t size);
void					list_item_delete(t_list_item *item);

typedef struct			s_list
{
	t_bool				is_valid;
	t_error_config		error_config;
	t_list_item			*begin;
	t_list_item			*end;
	size_t				element_size;
}						t_list;

t_list					list_create(size_t element_size);
void					list_destroy(t_list *list);

t_bool					list_verify(t_list *list);

t_list_item				*list_push(t_list *list, VOID_REF data);
t_bool					list_pop(t_list *list);

#endif
