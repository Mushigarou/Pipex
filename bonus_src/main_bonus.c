/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:46:05 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/27 00:04:49 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	// int	pipe_fd[ac-4][2];
	// int	i;
	// int	pid;
	
	// if (ac < 4)
	// {
	// 	perror("<./pipex> <infile> <cmd_1> ... <cmd_n> <outfile>");
	// 	exit(1);
	// }
	// i = 0;
	// pid = 0;
	// while (i < ac -4)
	// 	if (pipe(pipe_fd[i++]))
	// 		{perror("pipe");exit(1);}
	// i = 0;
	// while (i < ac - 3)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		if (i == 0)
	// 			first_cmd(av, env, pipe_fd[i], i);
	// 		else if (i == ac - 3)
	// 			last_cmd(ac, av, env, pipe_fd[i-1]);
	// 		else
	// 			middle_cmd(av, env, pipe_fd, i);
	// 		return ;
	// 	}
	// 	i++;
	// }
	// return 0;

}
