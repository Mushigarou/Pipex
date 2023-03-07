/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putstr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:21:11 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/07 23:14:48 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Outputs the string 's' to the given file descriptor.

#include "libft.h"

int	printf_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
	{
		len = write(1, "(null)", 6);
		return (len);
	}
	len = ft_strlen(s);
	write (fd, s, len);
	return (len);
}
