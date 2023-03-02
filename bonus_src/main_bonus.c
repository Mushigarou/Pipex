/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:46:05 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/02 02:27:22 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	fd[ac-4][2];
	int	i;
	int stat;
	int	pid;
	
	if (ac < 4 || !av || !(*av) || !env || !(*env))
	{
		perror("<./pipex> <infile> <cmd_1> ... <cmd_n> <outfile>");
		exit(1);
	}
	stat = 0;
	i = 0;
	pid = 0;
	while (i < ac - 4)
	{	
		if (pipe(fd[i]))
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
	printf("pipes = %d\n", i);
	i = 1;
	// int j = 0;
	// int fd[2];
	// pipe(fd);
	while (i <= ac - 3)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("fork() = %d | av[i+1] = %s | ac-3 = %d\n", i, av[i+1], ac);
			if (i == 1)
				{first_cmd(av, env, fd[i-1]);} // 0
			else if (i == ac-3)
				last_cmd(ac, av, env, fd[i-2]); // 1
			else
				middle_cmd(av[i+1], env, fd[i-2], fd[i-1]); // 0 1
			exit(1);
		}
		i++;
	}
	wait(&stat);
	if(WIFEXITED(stat))
	{
		stat = WEXITSTATUS(stat);
		if (stat != 0)
			exit(stat);
	}
	close_fd((int **)fd);
	return 0;
}
