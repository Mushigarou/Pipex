/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:32:00 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/07 23:16:06 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// **	Maximum nbr of fd's is 10240 per process or shell
// **	10240 /2 = 5120 pipes, since each pipe need 2 fd's
# define PIPES 5120
//**	Err message
# define CMD_SYNTAX "./pipex \"infile\" \"cmd_1 -options\"\
 ...\"cmd_n -options\" \"outfile\"\n"
# define CMD_SYNTAX_M "./pipex \"infile\" \"cmd_1 -options\"\
 \"cmd_2 -options\" \"outfile\"\n"

// **	Libft header
# include "../Libft/libft.h"
// **	get_next_line()
# include "../Libft/get_next_line.h"
// **	ft_printf()
# include "../Libft/ft_printf.h"
// **	exit(), malloc(), free()
# include <stdlib.h>
// **	sterror(), perror()
# include <stdio.h>
// **	read(), write(), close(), access(), dup(), dup2(), 
//			execve(), fork(), pipe(), unlink()
# include <unistd.h>
// **	open()
# include <fcntl.h>
// **	wait(), waitpid()
# include <sys/wait.h>
// **	Errno global variable
# include <errno.h>

typedef struct s_data{
	int		ac;
	int		pipes_nbr;
	char	**av;
	char	**env;
	int		stat;
	int		pid;
	int		fd[][2];
}	t_data;

// ** Print a message
void	msg(char *err, int status, int bool);
// **	Free memory allocated
void	free_st(char **split, int not_this_one);
// **	Get PATH variable from the environment, returns path of the command
char	*path_is(char **env, char *cmd);
// **	Read from the input file, then writes in the pipe
void	write_cmd(char **av, char **env, int fd[]);
// **	Reads from the pipe, then writes in outfile
void	read_cmd(char **av, char **env, int fd[]);
// **	Read from the input file, then writes in the pipe
void	first_cmd(char **av, char **env, int fd[]);

void	middle_cmd(char *av, char **env);

// **	Reads from the pipe, then writes in outfile
void	last_cmd(int ac, char **av, char **env, int fd[]);
// **	Closes all file descriptors
void	close_fd(int **fd);
// **	Checks return value of dup2()
void	ft_dup2(int old, int new, char *err);
// **	Closes all given pipes
void	close_pipes(int i, int ac, int fd[][2]);

#endif	// PIPEX_H
