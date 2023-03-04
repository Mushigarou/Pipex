/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:45:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/04 00:38:06 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_cmd(char *av, char **env)
{
	char	*path;
	char	**tmp;

	path = NULL;
	tmp = ft_split(av, ' ');
	if (!tmp || !(*tmp))
		msg("pipex: command not found\n", 127);
	path = path_is(env, tmp[0]);
	execve(path, tmp, env);
	msg("execve", 126);
}

// Opens the infile, then writes to the first pipe. finally, 
// executes first command
void first_cmd(char **av, char **env, int fd[])
{
	char *path;
	int in_fd;
	char **tmp;

	tmp = ft_split(av[2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127);
	path = NULL;
	in_fd = open(av[1], O_RDONLY);
	if (in_fd == -1)
		{perror("open 1");exit(1);}
	ft_dup2(in_fd, STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	path = path_is(env, av[2]);
	execve(path, tmp, env);
	msg("execve", 126);
}

void last_cmd(int ac, char **av, char **env, int fd[])
{
	char *path;
	int out_fd;
	char **tmp;

	path = NULL;
	tmp = ft_split(av[ac-2], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		{write(2, "pipex: command not found\n", 25);exit(127);}
	out_fd = open(av[ac-1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (out_fd == -1)
		{perror("open 2");exit(1);}
	ft_dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	close(fd[1]);
	close(fd[0]);
	path = path_is(env, av[ac-2]);
	execve(path, tmp, env);
	msg("execve", 126);
}

char *join_path(char **split, char *cmd)
{
	char **av_cmd;
	char *tmp;
	char *path;
	int i;

	i = 0;
	if (!cmd)
		msg("command not found", 1);
	av_cmd = ft_split(cmd, ' ');
	if (!split)
	{
		free_st(split, -1);
		msg("split", 1);
	}
	tmp = NULL;
	if (av_cmd[0][0] == '/')
	{
		if (access(av_cmd[0], X_OK | F_OK) == 0)
			return (fprintf(stderr, "\n%s\n", av_cmd[0]), free_st(split, -1), free(tmp), free_st(av_cmd, 0), av_cmd[0]);
		msg("access", 2);
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
	msg("pipex: command not found", 127);
	return (NULL);
}

char *path_is(char **env, char *cmd)
{
	char **split;

	split = NULL;
	if (!env || !(*env) || !cmd)
		msg("command or env not found", 1);
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			split = ft_split(*env + 5, ':');
			if (!split)
				msg("split", 2);
			return (join_path(split, cmd));
		}
		env++;
	}
	msg("PATH variable not found", 2);
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
