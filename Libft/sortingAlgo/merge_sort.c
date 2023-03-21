/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 04:37:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/18 05:51:52 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 	int	a[] = {6, 2, 3, 4};
// Merging subarrays into a sorted array
static void	sort_array(int a[], int p, int q, int r)
{
	p = 0;
	int	*l1;
	int *l2;
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	printf("p = %d | q = %d | r = %d | r-q = %d\n\n", p, q, r, r-q);
	l1 = (int *)malloc(q-p+1 * sizeof(int));
	l2 = (int *)malloc(r-q * sizeof(int));
	// while (++i < q+1)
	// 	l1[i] = a[i];
	i = 0;
	// while (i < r-q)
	// {
	// 	printf("\na[i] = %d\n", a[i]);
	// 	l2[i] = a[q+i];
		
	// 	i++;
	// }
	// i = q+1;
	l1 = (int *)ft_memcpy(l1, a, (q+1) * sizeof(int));
	// l2 = (int *)ft_memcpy(l2, &a[r-q], (r-q) * sizeof(int));
	for (int i = 0; i <= q; i++)
		printf("l1 :	%d ", l1[i]);
	printf("\n\n");
	k = 0;
	l2[0] = 0;
	printf("%d", l2[0]);
	for (int i = r-q; i < r; i++)
	{
		// printf("l2 :	%d \n", l2[k]);
		k++;
	}
	return ;
}

// p represents beginning of the subarray, and 'r' represents the end
void	merge_sort(int a[], int p, int r)
{
	int	q;
	int	i;
	
	i = 0;
	q = 0;
	if (p < r)
	{
		q = (p + r) / 2;
		// merge_sort(a, p, q);
		// merge_sort(a, q+1, r);
		sort_array(a, p, q, r);
	}
	return ;
}
