/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:40 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/07 22:52:17 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	p(char *file, int line, int msg)
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
	return ;
}

void	msg(char *err, int status, int bool)
{
	if (bool == 0)
	{
		perror(err);
		exit(status);
	}
	else
	{
		write(2, err, ft_strlen(err));
		exit(status);
	}
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
