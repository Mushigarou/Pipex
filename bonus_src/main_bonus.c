/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:46:05 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/13 03:13:53 by mfouadi          ###   ########.fr       */
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

void	exec_child(t_data data, int fd[2], int i)
{
	if (i == 0)
	{
		if (ft_strncmp(data.av[1], "here_doc", 9) == 0)
		{	
			if (data.ac < 6)
				msg(CMD_SYNTAX_H, 1, 1);
			here_document(data, fd);
		}
		else
			first_cmd(data.av, data.env, fd);
	}
	else if (i == data.ac - 4)
		last_cmd(data.ac, data.av, data.env, fd);
	else
		middle_cmd(data.av[i + 2], data.env, fd);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd[2];

	if (ac < 5 || !av || !(*av) || !env || !(*env))
		msg(CMD_SYNTAX, 1, 1);
	init_data(&data, ac, av, env);
	while (data.i < ac - 3)
	{
		if (pipe(fd) != 0)
			msg("pipe", 1, 0);
		data.pid = fork();
		if (data.pid == 0)
			exec_child(data, fd, data.i);
		ft_dup2(fd[0], STDIN_FILENO, "dup2_main");
		close(fd[0]);
		close(fd[1]);
		data.i++;
	}
	if (access(data.filename, F_OK) == 0)
		if (unlink(data.filename) != 0)
			msg("unlink", 2, 0);
	wait_childs(data.stat);
}
