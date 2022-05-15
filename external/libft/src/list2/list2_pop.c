/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:51:45 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:51:45 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

void					list2_pop(t_list2 *list)
{
	t_list2_node		*old_end;

	if (list->begin == list->end)
		list->begin = NULL;
	old_end = list->end;
	list->end = list->end->previous;
	list2_node_delete(old_end);
}
