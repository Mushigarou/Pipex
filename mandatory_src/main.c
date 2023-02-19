/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:36 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/19 06:08:46 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// **	 < file1 cmd1 | cmd2 > file2 ||  ./pipex infile "ls -l" "wc -l" outfile
/*
**	< test.txt grep a1 | cat outfile {successfuly} {exits}
**		only output of cat outfile is shown, result of grep doesn't show up
**
**	(0) < test.txt grep a1 | wc -w > outfile {successfuly}
**			outfile is created, and output of grep is in it
**
**	(0) < t.txt grep a1 | cat > outfile (t.txt doesn't exists)
**			zsh: no such file or directory: t.txt || {outfile is overwritten with nothing}
**			if outfile doesn't exists, it's created and it is empty
**
**	(0) test.txt < grep a1 | wc -w > outfile {outfile is created, and output of grep 0}
**			zsh: no such file or directory: grep
**
**	(1) test.txt < grep a1 | wc -w outfile (outfile doesn't exists)
**			zsh: no such file or directory: grep
**			wc: outfile: open: No such file or directory
**
**
**	(1) < test.txt grep a1 | wc -w outfile >
**			zsh: parse error near `\n'
**
**	(127) < test.txt grep a1 | > wc -w outfile
**			zsh: command not found: -w (wc file is createad but empty)
**
**	(1) < test.txt grep a1 | wc -w outfile {outfile doesn't exist}
**			wc: outfile: open: No such file or directory
**
*/

/*
**	EXECUTION LINE : When you call fork() the memory of main process is copied to the child's memory
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
**		Child's process  (in parent process) = parent's process (in child process)
**		parent's process (in parent process) is a unique pid
** 	getppid
**		Get parent or calling process identification

**	wait() :
**		If pid is -1, the call waits for any child process.
**		If pid is 0, then call waits for any child process in the process group of the caller.
**		If pid is greater than zero, the call waits for the process with process id pid.
**		If pid is less than -1, the call waits for any process whose process group id equals
**	 		the absolute value of pid.
**		The waitpid() call is identical to wait4() with an rusage value of zero.  The
**	 		older wait3() call is the same as wait4() with a pid value of -1.
**
** pipe() : returns two fd
**		fd[0] - read
**		fd[1] - write
**	To use a pipe, the two processes must be in the same hierarchy
*/
#include "pipex.h"

// **	ft_printf("%s line %d	", __FILE__, __LINE__, -1)

// ** Printing 1 -> 5 by child and 6 -> 10 by parent
// int	main(void)
// {
// 	int i = 0;
// 	int id = fork();
	
// 	wait(0);
// 	if (id == 0)
// 	{	while (i <= 5)
// 		{
// 			printf("Child id = %d | i = %d\n", id, i);
// 			fflush(stdout);
// 			i++;
// 		}
// 		printf("Child : %d | Parent : %d | id = %d\n", getpid(), getppid(), id);
// 	}
// 	else
// 	{
// 		i = 6;
// 		while (i <= 10)
// 		{
// 		    printf("Parent id = %d | i = %d\n", id, i);
// 			fflush(stdout);
// 			i++;
// 		}
// 		printf("Child : %d | Parent : %d | id = %d\n", getpid(), getppid(), id);
// 	}
	
// }

// ** Communicating between two processes
// int main()
// {
// 	int	fd[2];
// 	pipe(fd);

// 	int	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		write(fd[1], "hellojdj", 8);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		char *s;
// 		s = (char *)malloc(9);
// 		s[9] = '\0';
// 		close(fd[1]);
// 		read(fd[0], s, 9);
// 		close(fd[0]);
// 		printf("%s\n", s);
// 		free(s);
// 	}
// }

// **	Calculating half of the array by each process, then sum up everything
// int	main()
// {
// 	int arr[] = { 1, 2, 10, 100, 100};
// 	int fd[2];
// 	int	pid;
// 	int i = 0;
// 	int res = 0;

// 	if (pipe(fd) == -1)
// 		perror("pipe");
// 	if ((pid = fork()) == -1)
// 		perror("fork");
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		while ((unsigned long)i < ((sizeof(arr) / 4) / 2))
// 		{
// 			res += arr[i];
// 			i++;
// 		}
// 		if (write(fd[1], &res, sizeof(res)) == -1)
// 			perror("write");
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		if (read(fd[0], &res, sizeof(res)))
// 			perror("read");
// 		i = ((sizeof(arr) / 4) / 2);
// 		while ((unsigned long)i < (sizeof(arr) / 4))
// 		{
// 			res += arr[i];
// 			i++;
// 		}
// 		printf("Total = %d", res);
// 		close(fd[0]);
// 	}
// }


//	** calculating sum by using 3 processes
// int	main(int ac, char **av)
// {

// 	int pid;
// 	int pid1;
// 	int i = 2;
// 	int res = 0;
// 	int fd[2];
// 	int fd1[2];

// 	if (ac < 4)
// 		return (printf("More Integer Arguments..."), -1);
// 	while (av && av[i])
// 		i++;
// 	printf("i = %d | av[0] = %s\n", i, av[0]);
// 	int arr[i];
// 	i = 1;
// 	while (av && av[i])
// 	{
// 		arr[i] = ft_atoi(av[i]);
// 		i++;
// 	}
// 	unsigned int p1 = ((sizeof(arr) / 4) / 3);
// 	unsigned int p2 = (((sizeof(arr) / 4) / 3) * 2);
// 	unsigned int p3 = ((sizeof(arr) / 4));

// 	if (pipe(fd) == -1)
// 		return (2);
// 	if (pipe(fd1) == -1)
// 		return (perror("pipe fd1"), 8);
// 	if ((pid = fork()) == -1)
// 		return (1);
// 	// wait(NULL);
// 	i = 1;
// 	if (pid == 0)
// 	{
// 		if ((pid1 = fork()) == -1)
// 			return (3);
// 		// wait(NULL);
// 		if (pid1 == 0)
// 		{
// 			close(fd1[0]);
// 			while ((unsigned int)i < p1)
// 			{
// 				res += arr[i];
// 				i++;
// 			}
// 			if (write(fd1[1], &res, sizeof(res)) == -1)
// 				return (4);
// 			close(fd1[1]);
// 		}
// 		if (read(fd1[0], &res, sizeof(res)) == -1)
// 			return (5);
// 		close(fd[0]);
// 		close(fd1[0]);
// 		i = p1;
// 		while ((unsigned int)i < p2)
// 		{
// 			res += arr[i];
// 			i++;
// 		}
// 		if (write(fd[1], &res, sizeof(res)) == -1)
// 			return (perror("write"), printf("errno=%d\n", errno), 6);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		if (read(fd[0], &res, sizeof(res)) == -1)
// 			return (7);
// 		close(fd[0]);
// 		i = p2;
// 		while ((unsigned int)i < p3)
// 		{
// 			res += arr[i];
// 			i++;
// 		}
// 		printf("Total = %d", res);
// 	}
// 	return (0);
// }

#include <sys/types.h>
#include <sys/stat.h>
// **	FIFO's in Unix : is a type file that can be used as a pipe
int	main()
{
	mkfifo("testing", 0777);
	return (0);
}
