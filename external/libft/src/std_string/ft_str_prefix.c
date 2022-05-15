/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:10:42 by bshanae           #+#    #+#             */
/*   Updated: 2019/04/05 15:14:40 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_standart.h"

int					ft_str_prefix(const char *string, const char *prefix)
{
	while (*string)
	{
		if (!*prefix)
			return (1);
		if (*string != *prefix)
			return (0);
		string++;
		prefix++;
	}
	return (0);
}
