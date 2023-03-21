/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 04:32:00 by mfouadi           #+#    #+#             */
/*   Updated: 2023/03/21 00:32:37 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//**	Err message
# define CMD_SYNTAX "./pipex \"infile\" \"cmd_1 -options\"\
 ...\"cmd_n -options\" \"outfile\"\n"
# define CMD_SYNTAX_M "./pipex \"infile\" \"cmd_1 -options\"\
 \"cmd_2 -options\" \"outfile\"\n"
# define CMD_SYNTAX_H "./pipex here_doc DELIMITER \"cmd_1 -options\"\
 ...\"cmd_n -options\" \"outfile\"\n"

// **	Libft header
# include "../Libft/inc/libft.h"
// **	get_next_line()
# include "../Libft/inc/get_next_line.h"
// **	ft_printf()
# include "../Libft/inc/ft_printf.h"
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
// **	for 'bool' type
# include <stdbool.h>

typedef struct s_data
{
	char	**av;
	char	**env;
	int		ac;
	char	*filename;
	int		pid;
	int		stat;
	int		i;

}	t_data;

// ** Print a message
void	msg(char *err, int status, int bol);
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

void	middle_cmd(char *av, char **env, int fd[2]);

// **	Reads from the pipe, then writes in outfile
void	last_cmd(int ac, char **av, char **env, int fd[]);
// **	Checks return value of dup2()
void	ft_dup2(int old, int new, char *err);

void	here_document(t_data data, int fd[]);

char	*heredoc_filename(t_data *data);

void	init_data(t_data *data, int ac, char **av, char **env);

#endif // PIPEX_H
