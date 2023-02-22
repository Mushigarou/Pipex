/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:40 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/22 05:42:10 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	p(char *file, int line, int msg)
{
	if (msg == 0 && file && line != 0)
		ft_printf("%s line %d	", file, line, -1);
	else if (msg == 1)
		ft_printf("./pipex infile cmd1 cmd2 outfile");
	return;
}

// **	if not_this_one is set, it will free all the pointers,
// **		but not the one holding the path of the cmd
// **		otherwise not_this one = -1 (all will be freed)
void	free_st(char **split, int not_this_one)
{
	int	i;

	i = 0;
	if (split || *split)
		return ;
	while (split && *split)
	{
		if (i != not_this_one)
			free(*split);
		split++;
	}
	free(split);
}
