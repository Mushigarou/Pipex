/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:46 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/23 02:17:28 by mfouadi          ###   ########.fr       */
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
	tmp = ft_strjoin("/", av_cmd[0]);
	free_st(av_cmd, -1);
	while (split && split[i])
	{
		if (access(av_cmd[0], X_OK | F_OK) == 0)
			return (free(tmp), free_st(av_cmd, 0), av_cmd[0]);
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
	// char	**tmp;
	
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
		//strnstr(*env, "PWD=")
		env++;
	}
	return (NULL);
}
