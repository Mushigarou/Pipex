/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:46:05 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/03 06:40:13 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_child(int stat)
{
	// int stat;
	wait(&stat);
	if (WIFEXITED(stat))
		if ((stat = WEXITSTATUS(stat)))
			if (stat != 0)
				exit(stat);
}

/*
void init_data(int ac, char **av, char **env, t_data *data)
{
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->pid = 0;
	data->stat = 0;
}
*/
int	main(int ac, char **av, char **env)
{
	int	fd[ac-4][2];
	int	i;
	int stat;
	int	pid;

// t_data data;
//		data.arr_size = ac - 4;
// 		data.ac = ac;
// 		data.av = av;
// 		data.env = env;
// 		data.pid = 0;
// 		data.stat = 0;

	stat = 0;
	i = -1;
	pid = 0;
	// init_data(ac, av, env, &data)
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
		{
			if (i == 0)
				{
					int j = 0;
					while (j < ac - 4)
					{
						close(fd[j][0]);
						if (j != i)
							close(fd[j][1]);
						j++;
					}
					first_cmd(av, env, fd[i]);
				}
			else if (i == ac-4)
			{
				// int j = 0;
				// while (j < ac - 4)
				// {
				// 	// printf i
				// 	if (j != i)
				// 		close(fd[j][0]);
				// 	close(fd[j][1]);
				// 	j++;
				// }
				last_cmd(ac, av, env, fd[i-1]);
			}
			else
				middle_cmd(av[i+2], env);
			exit(1);
		}
		if (i < ac - 4)
		{
			ft_dup2(fd[i][0], STDIN_FILENO);
			close(fd[i][0]);
			close(fd[i][1]);
			ft_dup2(fd[i+1][1], STDOUT_FILENO);
		}
		i++;
		wait_child(stat);
	}
	return 0;
}
