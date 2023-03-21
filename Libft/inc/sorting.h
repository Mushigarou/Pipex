/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 06:20:20 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/18 03:29:15 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SORTING_H
# define SORTING_H

# include "libft.h"

void	bubble_sort(int a[], int n);
void	opt_bubble_sort(int a[], int n);
void	insertion_sort(int a[], int n);
void	selection_sort(int a[], int n);
void	merge_sort(int a[], int p, int r);

#endif // SORTING_H

