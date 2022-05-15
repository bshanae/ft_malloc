/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_node_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:51:31 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:51:31 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

void					list2_node_delete(t_list2_node *node)
{
	if (node->previous)
		node->previous->next = NULL;
	if (node->next)
		node->next->previous = NULL;
	node->previous = NULL;
	node->next = NULL;
	free(node->data);
	node->data = NULL;
}
