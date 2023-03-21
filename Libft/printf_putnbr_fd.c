/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:16:34 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/07 23:14:44 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Outputs the integer n to the given file descriptor

#include "libft.h"

int	printf_putnbr_fd(int n, int fd)
{
	int	len;

	len = 0;
	if (n == INT_MIN)
	{
		len += write(fd, "-2147483648", 11);
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
		len += printf_putnbr_fd(n / 10, fd);
		len += printf_putnbr_fd(n % 10, fd);
	}
	return (len);
}
