/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:45:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/02 02:27:24 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_cmd(char *av, char **env, int r_fd[], int w_fd[])
{
	char	*path;
	char	**tmp;

	path = NULL;
	tmp = ft_split(av, ' ');
	if (!tmp || !(*tmp))
	{
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	// printf("Mid: i == %d \n", i);
	dup2(r_fd[0], STDIN_FILENO);
	dup2(w_fd[1], STDOUT_FILENO);
	printf("av == %s | tmp[0] == %s\n", av, tmp[0]);
	if (!(path = path_is(env, tmp[0])))
	{
		perror("pipex");
		exit(127);
	}
	// close_fd(&r_fd);
	// close_fd(&w_fd);
	// fprintf(stdout, "Middle : tmp[0] = %s | tmp[1] = %s | path = %s\n", tmp[0], tmp[1], path);
	// fflush(stdout);
	execve(path, ft_split(av, ' '), env);
	perror("execve 2");
	exit(126);
}

void first_cmd(char **av, char **env, int fd[])
{
	char *path;
	int in_fd;
	char **tmp;

	tmp = ft_split(av[2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
	{
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	path = NULL;
	close(fd[0]);
	in_fd = open(av[1], O_RDONLY);
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
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	fprintf(stdout, "First : av[1] = %s | tmp[0] = %s | tmp[1] = %s | path = %s\n", av[1], tmp[0], tmp[1], path);
	execve(path, ft_split(av[2], ' '), env);
	perror("execve 1");
	exit(126);
}

void last_cmd(int ac, char **av, char **env, int fd[])
{
	char *path;
	int out_fd;
	char **tmp;

	tmp = ft_split(av[ac-2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
	{
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	path = NULL;
	close(fd[1]);
	out_fd = open(av[ac-1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (out_fd == -1)
	{
		perror("open 2");
		exit(1);
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (!(path = path_is(env, av[ac-2])))
	{
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	fprintf(stdout, "Last : ac-1 = %s | tmp[0] = %s | tmp[1] =%s | path = %s\n", av[ac-1], tmp[0], tmp[1], path);
	if (execve(path, ft_split(av[ac-2], ' '), env) < 0)
		perror("execve 3");
	exit(126);
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
			return (fprintf(stderr, "\n%s\n", av_cmd[0]), free_st(split, -1), free(tmp), free_st(av_cmd, 0), av_cmd[0]);
		else
		{
			perror("access");
			exit(2);
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
	write(2, "pipex: command not found\n", 25);
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
