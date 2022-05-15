/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:52:51 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:52:51 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

void					list2_remove(t_list2 *list, t_list2_node *target)
{
	t_list2_node		*previous;
	t_list2_node		*next;

	if (!target)
		return (list2_pop(list));
	if (list->begin == target)
		list->begin = target->next;
	if (list->end == target)
		list->end = target->previous;
	previous = target->previous;
	next = target->next;
	list2_node_delete(target);
	list2_node_connect(previous, next);
}
