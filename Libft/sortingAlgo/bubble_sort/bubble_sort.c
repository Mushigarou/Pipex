/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:13:46 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/17 05:47:53 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

static void swap_int(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void	bubble_sort(int a[], int n)
{
	int k;

	while (--n)
	{
		k = -1;
		while (++k < n)
			if (a[k] > a[k + 1])
				swap_int(&a[k], &a[k + 1]);
	}
	return;
}
