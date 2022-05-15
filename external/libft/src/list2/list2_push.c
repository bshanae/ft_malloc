/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:52:58 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:52:58 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

t_list2_node			*list2_push(t_list2 *list, VOID_REF data)
{
	t_list2_node		*node;

	if (!(node = list2_node_new(data, list->element_size)))
		return (NULL);
	if (!list->begin)
		list->begin = node;
	else
		list2_node_connect(list->end, node);
	list->end = node;
	return (node);
}
