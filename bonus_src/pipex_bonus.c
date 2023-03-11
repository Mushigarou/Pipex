/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 02:45:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/11 09:38:48 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	msg("pipex: command not found", 127, 1);
	return (NULL);
}

char	*join_path(char **env_path, char *cmd)
{
	char	**av_cmd;
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd)
		msg("pipex: command not found", 1, 1);
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
		msg("pipex: command or env not found", 1, 1);
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
	msg("pipex: environment path variable not found", 2, 1);
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
