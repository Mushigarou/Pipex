/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putunbr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 06:11:11 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/07 23:14:52 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_putunbr_fd(unsigned int n, int fd)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len = write(fd, "0", 1);
		return (len);
	}
	else if ((long long)n < INT_MIN)
		return ((len += write(fd, "-1", 1)), len);
	if (n < 0)
	{
		len += printf_putchar_fd('-', fd);
		n *= -1;
	}	
	if (ft_isdigit(n + '0'))
		len += printf_putchar_fd(n + 48, fd);
	if (n > 9)
	{
		len += printf_putunbr_fd(n / 10, fd);
		len += printf_putunbr_fd(n % 10, fd);
	}
	return (len);
}
