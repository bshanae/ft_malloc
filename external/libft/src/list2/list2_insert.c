/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:52:16 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:52:19 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

t_list2_node		*list2_insert
	(t_list2 *list, t_list2_node *parent, VOID_REF data)
{
	t_list2_node	*old_child;
	t_list2_node	*new_child;

	if (!parent)
		return (list2_push(list, data));
	if (!(new_child = list2_node_new(data, list->element_size)))
		return (NULL);
	old_child = parent->next;
	list2_node_connect(parent, new_child);
	list2_node_connect(new_child, old_child);
	return (new_child);
}
