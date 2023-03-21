/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_bubble_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 05:33:38 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/17 06:13:07 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

static void swap_int(int *a, int *b, bool *sort)
{
	int tmp;

	*sort = 1;
	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void	opt_bubble_sort(int a[], int n)
{
	bool sorted;
	int k;

	while (--n)
	{
		k = -1;
		sorted = 0;
		while (++k < n)
			if (a[k] > a[k + 1])
				swap_int(&a[k], &a[k + 1], &sorted);
		if (!sorted)
			break;
	}
	return;
}
