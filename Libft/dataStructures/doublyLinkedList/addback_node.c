/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addback_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:10:24 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/18 18:55:27 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	addback_node(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	last = last_node(*lst);
	new->prev = last;
	last->next = new;
}
