/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:46 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/11 09:42:14 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_cmd(char **av, char **env, int fd[])
{
	char	*path;
	int		in_fd;
	char	**tmp;

	tmp = ft_split(av[2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127, 0);
	close(fd[0]);
	in_fd = open(av[1], O_RDONLY);
	if (in_fd == -1)
		msg("open", 2, 0);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	path = path_is(env, av[2]);
	if (!path)
		msg("pipex: command not found\n", 127, 1);
	execve(path, ft_split(av[2], ' '), env);
	msg("execve", 1, 0);
}

void	read_cmd(char **av, char **env, int fd[])
{
	char	*path;
	int		out_fd;
	char	**tmp;

	tmp = ft_split(av[3], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127, 1);
	path = NULL;
	out_fd = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (out_fd == -1)
		msg("open", 2, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	path = path_is(env, av[3]);
	if (!path)
		msg("pipex: command not found\n", 127, 1);
	execve(path, tmp, env);
	msg("execve", 1, 0);
}

char	*look_for_path(char **av_cmd, char **env_path)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	tmp = ft_strjoin("/", av_cmd[0]);
	free_st(av_cmd, -1);
	while (env_path && env_path[i])
	{
		if (i == 0)
			if (access(av_cmd[0], X_OK | F_OK) == 0)
				return (free_st(env_path, -1),
					free(tmp), free_st(av_cmd, 0), av_cmd[0]);
		path = ft_strjoin(env_path[i], tmp);
		if (access(path, X_OK | F_OK) == 0)
			return (free_st(env_path, -1),
				free(tmp), free_st(av_cmd, -1), path);
		free(path);
		i++;
	}
	free(tmp);
	free_st(env_path, -1);
	msg("pipex: command not found\n", 127, 1);
	return (NULL);
}

char	*join_path(char **env_path, char *cmd)
{
	char	**av_cmd;
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd)
		msg("pipex: command not found\n", 1, 1);
	av_cmd = ft_split(cmd, ' ');
	if (!env_path)
	{
		free_st(env_path, -1);
		msg("split", 1, 1);
	}
	tmp = NULL;
	if (av_cmd[0][0] == '/')
	{
		if (access(av_cmd[0], X_OK | F_OK) == 0)
			return (free_st(env_path, -1),
				free(tmp), free_st(av_cmd, 0), av_cmd[0]);
		msg("access", 2, 0);
	}
	return (look_for_path(av_cmd, env_path));
}

char	*path_is(char **env, char *cmd)
{
	char	**split;

	split = NULL;
	if (!env || !(*env) || !cmd)
		msg("pipex: missing environment path variable or command\n", 1, 1);
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			split = ft_split(*env + 5, ':');
			if (!split)
				msg("split", 2, 0);
			return (join_path(split, cmd));
		}
		env++;
	}
	msg("pipex: environment path variable not found\n", 2, 0);
	return (NULL);
}
