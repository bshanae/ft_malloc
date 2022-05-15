/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:51:23 by bshanae           #+#    #+#             */
/*   Updated: 2022/05/12 23:46:28 by v.belchenko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list2.h"

t_list2					list2_create(size_t element_size)
{
	t_list2				list;

	list.begin = NULL;
	list.end = NULL;
	list.element_size = element_size;
	return (list);
}
