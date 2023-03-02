/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:45:36 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/02 02:27:41 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "../include/pipex.h"

void p(char *file, int line, int msg)
{
	if (msg == 0 && file && line != 0)
		ft_printf("%s line %d	", file, line);
	else if (msg == 1)
		ft_printf("./pipex infile cmd1 cmd2 outfile");
	else if (msg == 2)
	{
		ft_printf("%s line %d	", file, line);
		ft_printf("PATH or command not found");
	}
	return;
}

// **	if not_this_one is set, it will free all the pointers,
// **		but not the one holding the path of the cmd
// **		otherwise not_this one = -1 (all will be freed)
void free_st(char **split, int not_this_one)
{
	int i;

	i = 0;
	if (split || *split)
		return;
	while (split && *split)
	{
		if (i != not_this_one)
			free(*split);
		split++;
	}
	free(split);
}

void	close_fd(int **fd)
{
	int	i;
	int size;
	
	if (!fd || !(*fd))
		return ;
	size = sizeof(fd) / sizeof(fd[i]);
	i = 0;
	while (i < size-1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}
