/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:16:32 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:43:05 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BTREE_H
# define LIBFT_BTREE_H

# include "libft_standart.h"
# include "libft_error.h"

typedef int				(*t_btree_f_cmp)(VOID_REF, VOID_REF);
typedef int				(*t_btree_f_del)(void *);
typedef void			(*t_btree_f_trv)(void *, void *);

typedef struct			s_btree_node
{
	void				*data;
	struct s_btree_node	*left;
	struct s_btree_node	*right;
}						t_btree_node;

t_btree_node			*btree_node_new(size_t size, VOID_REF data);
void					btree_node_delete(
	t_btree_node **node, t_btree_f_del del);

typedef struct			s_btree
{
	t_bool				is_valid;
	t_error_config		error_config;
	t_btree_node		*root;
	size_t				element_size;
	t_btree_f_cmp		f_cmp;
	t_btree_f_del		f_del;
}						t_btree;

t_btree					btree_create(
	size_t element_size, t_btree_f_cmp cmp);
void					btree_destroy(t_btree *btree);

t_btree_node			*btree_insert(t_btree *btree, VOID_REF data);
t_btree_node			*btree_remove(t_btree *btree, VOID_REF data);
t_btree_node			*btree_find(t_btree *btree, VOID_REF data);
t_btree_node			*btree_find_custom(
	t_btree *btree, t_btree_f_cmp cmp, VOID_REF data);

void					btree_prefix(
	t_btree *btree, t_btree_f_trv trv, void *ptr);
void					btree_infix(
	t_btree *btree, t_btree_f_trv trv, void *ptr);
void					btree_postfix(
	t_btree *btree, t_btree_f_trv trv, void *ptr);

#endif
