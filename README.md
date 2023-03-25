# Pipex
Pipex is a program that handles pipes and redirections in Unix / Linux systems.

For the mandatory part, here is the syntax that should be given to the program : 
            
             $> ./pipex infile cmd_1 cmd_2 outfile
For the bonus part, here is the syntax that should be given to the program : 
            
             $> ./pipex infile cmd_1 ... cmd_n outfile
The program supports heredocument too, here is the syntax that should be given to the program :

             $> ./pipex here_doc DELIMITER cmd_1 ... cmd_n outfile         
In the mandatoy part, I've created one pipe (pipe(2)) to communicate between the two child processes. Then, i forked (fork(2)) twice in the parent process, and i wait for the child processes before returning zero upon successful completion. 


To make a command write its output in the pipe, instead of STDOUT_FILENO, i used the dup2 (dup2(2)) function. 
Here is a visualisation of the program how it works in the mandatory part :

![Page_2_3](https://user-images.githubusercontent.com/115739322/226490616-32166bc2-e2c7-4d64-a587-e4fed3b45c85.png)

For the bonus part, we have to handle multiple pipes, and « and » when the first parameter is "here_doc".

This :

            $> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Should behave like :

            $> < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
And this :

            $> ./pipex here_doc LIMITER cmd cmd1 file
Should behave like 

            cmd << LIMITER | cmd1 >> file
Here is a visualisation of how to handle multiple pipes

![Page_1_4](https://user-images.githubusercontent.com/115739322/227705339-e15003c5-fde2-4436-98b3-8912e3870d32.png)
