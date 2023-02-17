/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:44:36 by mfouadi           #+#    #+#             */
/*   Updated: 2023/02/17 06:17:08 by mfouadi          ###   ########.fr       */
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
**	EXECUTION LINE
**								   ___  Parent id[x]
**								  |
** -------------------- FORK()----
**								  |___  Child id[0], ID of the child is always 0
**
**
*/
#include "pipex.h"
#include <fcntl.h>
// **	ft_printf("%s line %d	", __FILE__, __LINE__, -1)
int	main(void)
{
	int i = 0;
	int id = fork();
	
	if (id == 0)
		while (i <= 5)
		{
			printf("Child id = %d | i = %d\n", id, i);
			fflush(stdout);
			i++;
		}
	else
	{
		wait(0);
		i = 6;
		while (i <= 10)
		{
			printf("Parent id = %d | i = %d\n", id, i);
			fflush(stdout);
			i++;
		}
	}
}
