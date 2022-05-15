/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_node_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:52:05 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:52:05 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

t_list2_node			*list2_node_new(VOID_REF data, size_t data_size)
{
	t_list2_node		*node;

	if (!(node = malloc(sizeof(t_list2_node))))
		return (NULL);
	if (!(node->data = malloc(sizeof(data_size))))
	{
		free(node);
		return (NULL);
	}
	if (data)
		ft_memcpy(node->data, data, data_size);
	node->next = NULL;
	node->previous = NULL;
	return (node);
}
