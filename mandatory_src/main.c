/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:36 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/22 06:20:37 by mfouadi          ###   ########.fr       */
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

//p(__FILE__, __LINE__);
int main(int ac, char **av, char **env)
{
	char	*path;
	
	if (ac != 5)
		return (p(NULL, 0, 1), 0);
	// if (!path)
	// 	return (path env var doesn\'t exists, or )

	path = path_is(env, av[1]); // child
	printf("%s\n", path);
	// path = path_is(env, av[3]); // parent
	// pipe(fd);
	return (0);
}
