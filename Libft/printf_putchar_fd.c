/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putchar_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:16:43 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/15 19:33:03 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Outputs the character 'c' to the given file descriptor

#include "libft.h"

int	printf_putchar_fd(char c, int fd)
{
	return (write (fd, &c, 1));
}
