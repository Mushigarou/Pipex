/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:36 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/07 23:05:22 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	EXECUTION LINE : When you call fork() the memory of main process is
**		copied to the child's memory
**								   ___  Parent id[x]
**								  |
** -------------------- FORK()----
**								  |___  Child id[0], ID of the child is always 0
**
**	returned by fork()
**		Child's id = 0
**		Parent's id = 9407
**	Returned by getpid()
**		Child's process  (in child process) = 9407
**		Child's process  (in parent process) = 9406
**	Returned by getppid()
**		parent's process (in child process) = 9406
**		parent's process (in parent process) = 6907
**	************
**		parent's id = Child's process  (in child process)
**		Child's process  (in parent process) = parent's process(in child process
**		parent's process (in parent process) is a unique pid

*/
#include "pipex.h"

void	pipe_fork_exec(char **av, char **env, int fd[2])
{
	int	pid;
	int	id;

	id = 0;
	pid = 0;
	if (pipe(fd) == -1)
		msg("pipe", 2, 0);
	pid = fork();
	if (pid == -1)
		msg("fork_1", 2, 0);
	if (pid == 0)
		read_cmd(av, env, fd);
	id = fork();
	if (id == -1)
		msg("fork_2", 2, 0);
	if (id == 0)
		write_cmd(av, env, fd);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	stat;

	stat = 0;
	if (ac != 5 || !env || !(*env))
		msg(CMD_SYNTAX_M, 1, 1);
	pipe_fork_exec(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	wait(&stat);
	if (WIFEXITED(stat))
	{
		stat = WEXITSTATUS(stat);
		if (stat != 0)
			exit(stat);
	}
	return (0);
}
