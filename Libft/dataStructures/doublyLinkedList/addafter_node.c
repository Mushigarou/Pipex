/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addafter_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:44:16 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/19 08:20:16 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// **	Insert a node before a given node
void	addafter_node(t_node *prev_node, t_node *new_node)
{
	if (!prev_node)
		return ;
	// printf("new_node = %s", new_node->data);
	new_node->prev = prev_node;
	new_node->next = prev_node->next;
	prev_node->next = new_node;//
	if (new_node->next)
		new_node->next->prev = new_node;
	return ;
}
