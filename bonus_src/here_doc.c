/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:10:22 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/11 09:39:29 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*heredoc_filename(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (++i < 100)
	{
		tmp = ft_itoa(i);
		data->filename = ft_strjoin("heredoc_", tmp);
		free(tmp);
		if (access(data->filename, F_OK) != 0)
			break ;
		free(data->filename);
	}
	return (data->filename);
}

int	read_stdin(t_data data, int in_fd)
{
	char	*p;
	char	*tmp;

	in_fd = open(data.filename, O_CREAT | O_RDWR, 0644);
	if (in_fd < 0)
		msg("open", 2, 0);
	while (1)
	{
		p = get_next_line(0);
		tmp = ft_strtrim(p, "\n");
		if (!p)
			msg("pipex: no input provided", 1, 1);
		if (ft_strncmp(data.av[2], tmp, ft_strlen(data.av[2]) + 1) == 0)
			break ;
		write(in_fd, p, ft_strlen(p));
		free(p);
		free(tmp);
	}
	return (in_fd);
}

void	here_document(t_data data, int fd[])
{
	char	**tmp;
	char	*path;
	int		in_fd;

	in_fd = 0;
	path = NULL;
	tmp = ft_split(data.av[3], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found\n", 127, 1);
	in_fd = read_stdin(data, in_fd);
	ft_dup2(in_fd, STDIN_FILENO, "dup2");
	ft_dup2(fd[1], STDOUT_FILENO, "dup2");
	close(fd[0]);
	close(fd[1]);
	close(in_fd);
	path = path_is(data.env, data.av[3]);
	execve(path, tmp, data.env);
	msg("execve", 126, 0);
}
