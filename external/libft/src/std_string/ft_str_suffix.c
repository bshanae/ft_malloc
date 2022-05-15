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

int					ft_str_suffix(const char *string, const char *suffix)
{
	int				string_i;
	int				suffix_i;

	string_i = ft_strlen(string);
	suffix_i = ft_strlen(suffix);
	while (string_i > 0)
	{
		if (suffix_i == 0)
			return (1);
		if (string[string_i] != suffix[suffix_i])
			return (0);
		string_i--;
		suffix_i--;
	}
	return (0);
}
