/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:46:05 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/04 01:39:08 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_child(int stat)
{
	wait(&stat);
	if (WIFEXITED(stat))
		if ((stat = WEXITSTATUS(stat)))
			if (stat != 0)
				exit(stat);
}

void dup_pipes(int i, int (*fd)[][2])
{
		ft_dup2((*fd)[i][0], STDIN_FILENO);
		close((*fd)[i][0]);
		close((*fd)[i][1]);
		ft_dup2((*fd)[i + 1][1], STDOUT_FILENO);
}

void exec_child(int ac, char **av, char **env, int (*fd)[][2], int i)
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
	/*
	void init_data(int ac, char **av, char **env, t_data *data)
	{
		data.arr_size = ac - 4;
		data->ac = ac;
		data->av = av;
		data->env = env;
		data->pid = 0;
		data->stat = 0;
	}
	*/
	int main(int ac, char **av, char **env)
{
	int	fd[ac-4][2];
	int	i;
	int stat;
	int	pid;

	stat = 0;
	i = -1;
	pid = 0;
	if (ac < 5 || !av || !(*av) || !env || !(*env))
			msg(CMD_SYNTAX, 1);
	while (++i < ac - 4)
		if (pipe(fd[i]))
			msg("pipe", 1);
	i = 0;
	while (i < ac - 3)
	{
		pid = fork();
		if (pid == 0)
			exec_child(ac, av, env, &fd, i);
		if (i < ac - 4)
		{
			// dup_pipes(i, &fd);
			ft_dup2(fd[i][0], STDIN_FILENO);
			close(fd[i][0]);
			close(fd[i][1]);
			ft_dup2(fd[i + 1][1], STDOUT_FILENO);
		}
		i++;
		wait_child(stat);
	}
	return 0;
}
