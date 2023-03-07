/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:46:05 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/06 05:11:36 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_childs(int stat)
{
	int	st;

	st = 0;
	wait(&stat);
	if (WIFEXITED(stat))
	{
		st = WEXITSTATUS(stat);
		if (st != 0)
			exit(st);
	}
}

void	dup_pipes(int ac, int i, int (*fd)[][2])
{
	ft_dup2((*fd)[i][0], STDIN_FILENO, "dup2:main");
	close((*fd)[i][0]);
	close((*fd)[i][1]);
	if (i < ac - 5)
		ft_dup2((*fd)[i + 1][1], STDOUT_FILENO, "dup2:main");
}

void	exec_child(int ac, char **av, char **env, int (*fd)[][2], int i)
{
	if (i == 0)
	{
		close_pipes(i, ac, (*fd));
		first_cmd(av, env, (*fd)[i]);
	}
	else if (i == ac - 4)
		last_cmd(ac, av, env, (*fd)[i - 1]);
	else
	{
		close_pipes(i, ac, (*fd));
		middle_cmd(av[i + 2], env);
	}
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	pid;
	int	stat;
	int	fd[PIPES][2];

	i = -1;
	pid = 0;
	if (ac < 5 || !av || !(*av) || !env || !(*env))
		msg(CMD_SYNTAX, 1, 1);
	while (++i < ac - 4)
		if (pipe(fd[i]))
			msg("pipe", 1, 0);
	i = 0;
	stat = 0;
	while (i < ac - 3)
	{
		pid = fork();
		if (pid == 0)
			exec_child(ac, av, env, &fd, i);
		if (i < ac - 4)
			wait_childs(stat);
		if (i < ac - 4)
			dup_pipes(ac, i, &fd);
		i++;
	}
}
