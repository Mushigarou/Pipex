/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:04:46 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/12 03:21:49 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_cmd(char *av, char **env, int fd[2])
{
	char	*path;
	char	**tmp;

	path = NULL;
	tmp = ft_split(av, ' ');
	if (!tmp || !(*tmp))
		msg("pipex: command not found\n", 127, 1);
	path = path_is(env, tmp[0]);
	ft_dup2(fd[1], STDOUT_FILENO, "dup2");
	close(fd[1]);
	close(fd[0]);
	execve(path, tmp, env);
	msg("execve", 126, 0);
}

// Opens the infile, then writes to the first pipe. finally,
// executes first command
void	first_cmd(char **av, char **env, int fd[])
{
	char	**tmp;
	char	*path;
	int		in_fd;

	tmp = ft_split(av[2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127, 1);
	path = NULL;
	in_fd = open(av[1], O_RDONLY);
	if (in_fd == -1)
		msg("open", 1, 0);
	ft_dup2(in_fd, STDIN_FILENO, "dup2");
	ft_dup2(fd[1], STDOUT_FILENO, "dup2");
	close(fd[1]);
	close(fd[0]);
	close(in_fd);
	path = path_is(env, av[2]);
	execve(path, tmp, env);
	msg("execve", 126, 0);
}

int	open_outfile(char **av, int ac, int out_fd)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		out_fd = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (out_fd == -1)
			msg("open", 1, 0);
	}
	else
	{
		out_fd = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (out_fd == -1)
			msg("open", 1, 0);
	}
	return (out_fd);
}

void	last_cmd(int ac, char **av, char **env, int fd[])
{
	char	**tmp;
	char	*path;
	int		out_fd;

	out_fd = 0;
	path = NULL;
	tmp = ft_split(av[ac - 2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127, 1);
	out_fd = open_outfile(av, ac, out_fd);
	ft_dup2(out_fd, STDOUT_FILENO, "dup2");
	close(out_fd);
	close(fd[1]);
	close(fd[0]);
	path = path_is(env, av[ac - 2]);
	execve(path, tmp, env);
	msg("execve", 126, 0);
}
