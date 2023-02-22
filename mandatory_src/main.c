/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:36 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/22 03:50:26 by mfouadi          ###   ########.fr       */
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

// **	FIFO's in Unix : is a type file that can be used as a pipe (ls -l)
// **	mkfifo() waits for its other end (if you open() the file, created
//**		by mkfifo(). open() will hang untill a reader from the file
// ** 		(i.e open another terminal then cat testing, or write another
// **		 program that reads from the FIFO then launch it)), and vice versa.
// **	if the flag of open() is O_WRONLY, you must open another processes for
// **		reading from the FIFO file, unless flag is O_RDWR so it can read
// **		and write. so, open doesn't hangs openned. you can create a
// **		FIFO file via the command {mkfifo "file_name"}
// int	main()
// {
// 	printf("\nMkfifo\n");
// 	if (mkfifo("testing", 0777) == -1)
// 		if (errno != EEXIST)
// 			return 4;
// 	printf("\nopenning\n");
// 	int fd = open("testing", O_RDWR);
// 	printf("\nopenned\n");
// 	if (write(fd, "hey", 3) == -1)
// 		return 2;
// 	printf("\nWritten\n");
// 	close(fd);
// 	return (0);
// }

// **	Send numbers to the child, Mutiply, send it back to the parent to print
// **	it on the screen. Created two pipes, so we can write and read without
// **	worrying about printing the res before child process finish.
// **	we don't risk to read our content
// int	main()
// {
// 	int fd[2]; // C ==> P
// 	int fd1[2]; // P ==> C
// 	int res = 0;

// 	if (pipe(fd) == -1)
// 		return (1);
// 	if (pipe(fd1) == -1)
// 		return (1);
// 	int pid = fork();
// 	if (pid == -1)
// 		return (2);
// 	if (pid != 0)
// 	{
// 		close(fd[0]);
// 		close(fd1[1]);
// 		if (read(fd1[0], &res, sizeof(int)) == -1)
// 			return (2);
// 		res *= 4;
// 		close(fd1[0]);
// 		if (write(fd[1], &res, sizeof(res)) == -1)
// 			return (perror("write"), 3);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		close(fd1[0]);
// 		int arr = 7;
// 		if (write(fd1[1], &arr, sizeof(int)) == -1)
// 			return (4);
// 		close(fd[1]);
// 		if (read(fd[0], &res, sizeof(res)) == -1)
// 			return (5);
// 		close(fd[0]);
// 		printf("res = %d\n", res);
// 	}
// 	return (0);
// }

/*
**	After calling exec() functions family, the whole process get replaced by
**		that new called process.
**	All instructions after execve() will no longer be executed, to get around
**		this, you could fork() then exec instructions with child, wait() in 
**		parent
*/
// int	main(int ac, char **av, char **env)
// {
// 	if (ac < 2)
// 		return (1);
// 	int pid = fork();
// 	if (pid == -1)
// 		return (3);
// 	if (pid == 0)
// 	{
// 		if (execve("/bin/ls", av, env) == -1)
// 		{
// 			perror("execve");
// 			return (2);
// 		}
// 		printf("\nBYE BYE THIS PRINTF\n");
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		printf("\nExecve() has finished\n");
// 	}
// 	return (0);
// }

/*	
**	exec -l -v -p -e ('p' and 'e' are optional, 'e' is for environment
**		, and 'p' is for the path variable if you specify execl(),
**		for the command in "const char *")
** 		you could specify the optionschar *arr[] = { "ls" "-l" NULL };
*/
/*
**	the zero in front of the permissions in open(), means that it's
**		an octal number
**	dup(p1) returns another fd that points to the same file
**	dup2(p1, p2) p1 is the fd that you want to clone, and p2 is the fd that
**		will be pointing to the same fd as p1
*/
// **	Checking Exit  status code, and changing STDOUT to point to a file
// **		then changing back STDOUT_FILENO to point to terminal
// int	main(int argc, char **av)
// {
// 	if (argc < 2)
// 		return (printf("Add Options for ls command\n"),10);
// 	int	pid = fork();
// 	if (pid == -1)
// 		return (2);
// 	if (pid == 0)
// 	{
// 		int fd = open("test/stdout.txt", O_WRONLY | O_CREAT, 0777);
// 		if (fd == -1)
// 			return (4);
// 		int du = dup(STDOUT_FILENO);
// 		int fd2 = dup2(fd, STDOUT_FILENO);
// 		if (fd2 == -1)
// 			return (5);
// 		int fo = fork();
// 		if (fo == 0)
// 			execve("/bin/ls", av, NULL);
// 		else
// 		{
// 			dup2(du, STDOUT_FILENO);
// 			printf("I'm the child\n");
// 		}
// 	}
// 	else
// 	{
// 		int wstatus;
// 		wait(&wstatus);
// 		if (WIFEXITED(wstatus))
// 		{
// 			int code_status;
// 		code_status = WEXITSTATUS(wstatus);
// 		if (code_status == 0)
// 			printf("Exited with success %d\n", code_status);
// 		else
// 			printf("failure with code status %d\n", code_status);
// 		}
// 		printf("I'm the parent\n");
// 	}
// }


// #include <signal.h>
// **	Signals in C. Send a SIGKILL to child process after 2seconds
// ** 		SIGCHILD used to tell the parent that the child finished 
// **		execution
// **		SIGSTOP and SIGCONT to stop and continue execution of a process
// int main()
// {
// 	int pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			printf("Ctrl ^ C Won't help you hhhh\n");
// 			usleep(50000);
// 		}
			
// 	}	
// 	else
// 	{
// 		sleep(2);
// 		kill(pid, SIGKILL);
// 		wait(NULL);
// 	}
// 	return (0);
// }

// ** you can send the size of an array before sending the array itself
// int main()
// {
// 	int fd[2];
// 	pipe(fd);
// 	int pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		int n = 7;
// 		int arr[] = { 1, 2, 3, 4, 5, 10, 11};
// 		write(fd[1], &n, sizeof(n));
// 		write(fd[1], arr, sizeof(arr));
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		wait(NULL);
// 		int n = 0;
// 		read(fd[0], &n, sizeof(n));
// 		int arr[n];
// 		read(fd[0], arr, sizeof(arr));
// 		close(fd[0]);
// 		int ar = (sizeof(arr) / sizeof(int));
// 		int res = 0;
// 		while(ar > 0)
// 		{
// 			ar--;
// 			res += arr[ar];
// 			printf("arr[%d] = %d\n", ar, arr[ar]);
// 		}
// 		printf("res = %d", res);
// 	}
// 	return (0);
// }

// Sending a string through a pipe, then print it by the child
// int	main(int ac, char **av)
// {
// 	if (ac < 2)
// 		return (printf("pass a string\n"), 3);
// 	int fd[2];
// 	if (pipe(fd) == -1)
// 		return (1);
// 	int pid = fork();
// 	if (pid == -1)
// 		return (2);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		int len = 0, i = 1;
// 		while (av && av[i])
// 		{
// 			len += ft_strlen(av[i]);
// 			i++;
// 		}
// 		len += i;
// 		write(fd[1], &len, sizeof(len));
// 		i = 1;
// 		while (av && av[i])
// 		{
// 			write(fd[1], av[i], ft_strlen(av[i]));
// 			write(fd[1], " ", 1);
// 			i++;
// 		}
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(fd[1]);
// 		int len = 0;
// 		read(fd[0], &len, sizeof(sizeof(char), len));
// 		char *s = (char *)malloc(len);
// 		s[len] = '\0';
// 		read(fd[0], s, len);
// 		printf("%s\n", s);
// 		free(s);
// 		close(fd[0]);
// 	}
// 	return (0);
// }


// **	Simulating pipe '|' operator in c
/*
**	cat test/stdout.txt | grep @
**	|					 |	  |
**	|__________________ Pipe _|
**		STDOUT				 STDIN
*/
// int	main(int ac, char **av, char **env)
// {
// 	int	fd[2];
// 	int pid = 0;
// 	int std = 0;
// 	if (ac < 2)
// 		return (printf("./bin/pipex \"File to read\""), 1);
// 	if (pipe(fd) == -1)
// 		return (2);
// 	std = dup(STDOUT_FILENO);
// 	if ((pid = fork()) == -1)
// 		return (3);
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve("/bin/cat", av, env);
// 	}
// 	if ((pid = fork()) == -1)
// 		return (4);
// 	if (pid == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve("/usr/bin/grep", (char *[]){"grep", "@", NULL}, env);
// 		// if (execlp("/usr/bin/grep", "grep", "@", NULL) == -1)
// 		// 	 	return 5;
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	wait(NULL);		
// }

int main(int ac, char **av)
{
	char **command1;
	char **command2;
	(void)ac;
	int fd[2];
	pipe(fd);

	pid_t pid1 = fork();
	//child1
	if(pid1 == 0)
	{
		command1 = ft_split(av[2], ' ');
		close(fd[0]);
		int fd_infile = open(av[1], O_RDONLY, 0777);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execvp(command1[0], command1);
	}
	else
	{
		command2 = ft_split(av[3], ' ');
		pid_t pid2 = fork();
		//child 2
		if(pid2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			int fd_outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
			dup2(fd_outfile, STDOUT_FILENO);
			close(fd_outfile);
			execvp(command2[0], command2);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
		printf("ALL DONE!!");
	}
	// int fd = open("infile", O_RDONLY, 0777);
	
}
