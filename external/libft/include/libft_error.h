/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <bshanae@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:00:01 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 17:00:01 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ERROR_H
# define LIBFT_ERROR_H

# include "libft_standart.h"

typedef struct		s_error_config
{
	t_bool			message_print;
	char			warning_prefix[64];
	t_bool			warning_as_error;
	char			error_prefix[64];
}					t_error_config;

t_error_config		error_config_create(void);

void				ft_print_warning(t_error_config *config, CHAR_REF message);
void				ft_print_error(t_error_config *config, CHAR_REF message);

void				ft_raise_warning(t_error_config *config, CHAR_REF message);
void				ft_raise_error(t_error_config *config, CHAR_REF message);

void				ft_assert(
	t_error_config *config, int statement, CHAR_REF message);
void				ft_assert_critical(
	t_error_config *config, int statement, CHAR_REF message);

void				*ft_malloc(t_error_config *config, u_long size);

#endif
