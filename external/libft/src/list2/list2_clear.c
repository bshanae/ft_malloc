/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:50:45 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:50:45 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

void					list2_clear(t_list2 *list)
{
	t_list2_node		*iter;
	t_list2_node		*target;

	iter = list->begin;
	while (iter)
	{
		target = iter;
		iter = iter->next;
		list2_node_delete(target);
	}
	list->begin = NULL;
	list->end = NULL;
}
