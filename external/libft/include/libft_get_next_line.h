/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshanae <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:16:26 by bshanae           #+#    #+#             */
/*   Updated: 2019/12/18 16:57:23 by bshanae          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GET_NEXT_LINE_H
# define LIBFT_GET_NEXT_LINE_H

# define BUFF_SIZE 2048

# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include "stdlib.h"
# include "libft_standart.h"

int					ft_new_line(char **s, char **line, int fd, int ret);
int					get_next_line(const int fd, char **line);

#endif
