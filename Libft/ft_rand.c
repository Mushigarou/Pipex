/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:06:17 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/11 06:45:54 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Generate random numbers between 0 and 1000000
**	x(n+1) = (a * x(n) + c) % m // Linear congruential generator
**		m, 0 < m — the "modulus"
**		a , 0 < a < m — the "multiplier"
**		c , 0 ≤ c < m — the "increment"
**		X0 , 0 ≤ X0 < m  the "seed" or "start value"
*/

unsigned long long	ft_rand(void)
{
	static unsigned long long	rand;

	rand = rand * 1103515245 + 12345;
	return ((unsigned long long)(rand) % 2147483648);
}
