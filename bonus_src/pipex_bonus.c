/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:45:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/27 02:08:23 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *middle_cmd(char **av, char **env, int *fd[], int i)
{
	char *path;
	// int in_fd;

	path = NULL;
	dup2(fd[i-1][0], STDIN_FILENO);
	dup2(fd[i][1], STDOUT_FILENO);
	
	if (!(path = path_is(env, av[i])))
	{
		perror("pipex");
		exit(127);
	}
	execve(path, ft_split(av[i], ' '), env);
	return (NULL);
}

char *first_cmd(char **av, char **env, int fd[])
{
	char *path;
	int in_fd;

	path = NULL;
	close(fd[0]);
	in_fd = open(av[1], O_RDONLY, 0444);
	if (in_fd == -1)
	{
		perror("open 1");
		exit(1);
	}
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (!(path = path_is(env, av[2])))
	{
		perror("pipex");
		exit(127);
	}
	execve(path, ft_split(av[2], ' '), env);
	return (NULL);
}

char *last_cmd(int ac, char **av, char **env, int fd[])
{
	char *path;
	int out_fd;

	path = NULL;
	out_fd = open(av[ac-1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (out_fd == -1)
	{
		perror("open 2");
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (!(path = path_is(env, av[3])))
	{
		perror("pipex");
		exit(127);
	}
	// closefd
	execve(path, ft_split(av[3], ' '), env);
	return (NULL);
}
char *join_path(char **split, char *cmd)
{
	char **av_cmd;
	char *tmp;
	char *path;
	int i;

	i = 0;
	if (!cmd)
		return (NULL);
	av_cmd = ft_split(cmd, ' ');
	if (!split)
		return (free_st(split, -1), NULL);
	tmp = NULL;
	if (av_cmd[0][0] == '/')
	{
		if (access(av_cmd[0], X_OK | F_OK) == 0)
			return (free_st(split, -1), free(tmp), free_st(av_cmd, 0), av_cmd[0]);
		else
		{
			perror("access");
			exit(127);
		}
	}
	tmp = ft_strjoin("/", av_cmd[0]);
	free_st(av_cmd, -1);
	while (split && split[i])
	{
		if (i == 0)
			if (access(av_cmd[0], X_OK | F_OK) == 0)
				return (free_st(split, -1), free(tmp), free_st(av_cmd, 0), av_cmd[0]);
		path = ft_strjoin(split[i], tmp);
		if (access(path, X_OK | F_OK) == 0)
			return (free_st(split, -1), free(tmp), free_st(av_cmd, -1), path);
		free(path);
		i++;
	}
	free(tmp);
	free_st(split, -1);
	exit(127);
	return (NULL);
}

char *path_is(char **env, char *cmd)
{
	char **split;

	split = NULL;
	if (!env || !(*env) || !cmd)
		return (NULL);
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			split = ft_split(*env + 5, ':');
			if (!split)
				return (perror("split"), NULL);
			return (join_path(split, cmd));
		}
		env++;
	}
	exit(1);
	return (NULL);
}

/*

int i = 0;
char *filename;
char *tmp;
while (1)
{
	tmp = ft_itoi(i);
	filename = strjoin("heredoc_", tmp);
	free(tmp);
	if (access(filename, F_OK) == 0) {
		return filename;
	}
	free(filename);
	i++;
}

*/
