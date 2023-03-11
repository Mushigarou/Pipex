/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:10:22 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/11 06:50:34 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char *heredoc_filename(int *i)
// {
// 	char *filename;
// 	char *tmp;
// 	int fd;

// 	tmp = ft_itoa((*i));
// 	if (!tmp)
// 		msg("malloc", 2, 0);
// 	filename = ft_strjoin("heredoc_", tmp);
// 	free(tmp);
// 	*i++;
// 	return (filename);
// }

void here_document(t_data data, int fd[])
{
	char **tmp;
	char *path;
	char *p;

	path = NULL;
	tmp = ft_split(data.av[3], ' ');
	if (tmp == NULL || tmp[0] == NULL)
		msg("pipex: command not found:1st_cmd\n", 127, 1);
	data.filename = ft_strjoin("here_doc_", ft_itoa(ft_rand()));
	int in_fd = open(data.filename, O_CREAT | O_RDWR, 0644);
	if (in_fd < 0)
		msg("open", 2, 0);
	while (1)
	{
		p = get_next_line(0);
		if (!p)
			msg("No input provided", 1, 1);
		if (ft_strncmp(data.av[2], ft_strtrim(p, "\n"), ft_strlen(data.av[2])+1) == 0)
			break;
		write(in_fd, p, ft_strlen(p));
		free(p);
	}
	ft_dup2(in_fd, STDIN_FILENO, "dup2_heredoc");
	ft_dup2(fd[1], STDOUT_FILENO, "dup2_heredoc");
	close(fd[0]);
	close(fd[1]);
	close(in_fd);
	path = path_is(data.env, data.av[3]);
	execve(path, tmp, data.env);
	msg("execve", 126, 0);
}
