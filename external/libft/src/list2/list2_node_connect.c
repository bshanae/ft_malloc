/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_node_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:51:15 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:51:15 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

void					list2_node_connect(
	t_list2_node *left, t_list2_node *right)
{
	if (left)
		left->next = right;
	if (right)
		right->previous = left;
}
