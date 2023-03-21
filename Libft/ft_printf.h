/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 04:09:28 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/15 19:41:50 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef STDOUT
#  define STDOUT 1
# endif // STDOUT

# include "libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int			ft_printf(const char *fmt, ...);
long	long	wr_address(unsigned long x);
int			ft_putunbr_fd(unsigned int n, int fd);
void		conv_hex(unsigned int x, int *len, int sp);

#endif // FT_PRINTF_H
