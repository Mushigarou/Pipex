/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:13:49 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/17 05:52:26 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	swap_int(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	insertion_sort(int a[], int n)
{
	int	i;
	int	j;
	
	i = 1;
	while (i < n)
	{
		j = i;
		while (j > 0 && a[j-1] > a[j])
		{
			swap_int(&a[j], &a[j-1]);
			j--;
		}
		i++;
	}
	return;
}
