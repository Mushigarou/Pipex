/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:46 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/24 01:26:24 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    These are system calls or functions provided by the operating system to interact with the file system, 
    processes and other system resources. They are used to perform various operations such as process creation, 
    file manipulation, and I/O operations. Some of these functions are related to pipes and redirections, while others are not.

    access(): This function is used to check the accessibility of a file. It takes a pathname and a mode as arguments and 
    returns 0 if the file can be accessed according to the specified mode, otherwise, it returns -1.

    dup() and dup2(): These functions are used to create a copy of a file descriptor. The dup() function creates 
    a new file descriptor that refers to the same file as the original file descriptor, while dup2() creates a new file 
    descriptor that refers to the same file as the original file descriptor and also allows you to specify the new file 
    descriptor number. These functions are useful for redirecting input and output streams in C programming.

    execve(): This function is used to replace the current process image with a new one. It takes the pathname of the 
    new process image and an array of arguments as arguments and it is commonly used to run other programs in a shell.

    exit(): This function is used to terminate the current process.

    fork(): This function creates a new child process that is a copy of the calling process. The parent and child processes 
    run concurrently and communicate with each other using pipes or other IPC mechanisms.

    pipe(): This function creates a pipe, a unidirectional communication channel between two processes. One end of the pipe 
    is for reading and the other end is for writing. The pipe file descriptors are returned in an array passed as an argument.

    unlink() : This function is used to remove a file or a directory.

    wait() and waitpid(): These functions are used to wait for the termination of a child process. wait() waits for any 
    child process to terminate, while waitpid() waits for a specific child process identified by its process ID.

    All of these functions can be used to perform different operations that can help in creating, managing and manipulating 
    processes and system resources. Redirection and pipes are used to handle input and output streams, and these functions 
    can be used in conjunction with redirection and pipes to perform specific operations.
*/

#include "pipex.h"

char	*read_cmd(char **av, char **env, int fd[])
{
	char	*path;
	int		in_fd;

	path = NULL;
	close(fd[0]);
	in_fd = open(av[1], O_RDONLY, 0777);
	if (in_fd == -1)
		return (perror("open 1"), NULL);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (!(path = path_is(env, av[2])))
		return (p(__FILE__, __LINE__, 2), NULL);
	execve(path, ft_split(av[2], ' '), env);
	return (NULL);
}

char	*write_cmd(char **av, char **env, int fd[])
{
	char	*path;
	int		out_fd;

	path = NULL;
	out_fd = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (out_fd == -1)
		return (perror("open 2"), NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	if (!(path = path_is(env, av[3])))
		return ((p(__FILE__, __LINE__, 2), NULL));
	execve(path, ft_split(av[3], ' '), env);
	return (NULL);
}
char	*join_path(char **split, char *cmd)
{
	char	**av_cmd;
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	av_cmd = ft_split(cmd, ' ');
	if (!split)
		return (free_st(split, -1), NULL);
	tmp = ft_strjoin("/", av_cmd[0]);
	free_st(av_cmd, -1);
	while (split && split[i])
	{
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
	return (NULL);
}

char *path_is(char **env, char *cmd)
{
	char	**split;
	
	split = NULL;
	if (!env || !(*env) || !cmd)
		return (NULL);
	while (env && *env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			split = ft_split(*env + 5, ':');
			if (!split)
				return (p(__FILE__, __LINE__, 0), perror("split"), NULL);
			return (join_path(split, cmd));
		}
		env++;
	}
	return (NULL);
}
