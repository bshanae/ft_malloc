/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:36:57 by bshanae           #+#    #+#             */
/*   Updated: 2019/04/12 14:14:21 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_standart.h"

int					helper_sign(const char *str, int *counter)
{
	if (str[0] == '-')
	{
		(*counter)++;
		return (-1);
	}
	else
		return (+1);
}

double				ft_atof(const char *str, int *length)
{
	int				counter;
	int				power;
	double			result;
	int				sign;

	counter = 0;
	power = 0;
	result = 0.;
	sign = helper_sign(str, &counter);
	while (is_dec(str + counter))
	{
		result = result * 10. + (str[counter] - '0');
		counter++;
	}
	if (str[counter++] == '.')
		while (is_dec(str + counter))
		{
			result = result * 10. + (str[counter] - '0');
			power++;
			counter++;
		}
	while (--power >= 0)
		result *= 0.1;
	if (length)
		*length = counter;
	return ((double)sign * result);
}
