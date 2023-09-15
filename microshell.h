#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>


int	main(int argc, char **argv, char **envp);
int	error_message(char *s1, char *s2);
int	ft_cd(char **argv, int i);
int	ft_executer(char **argv, int i, char **envp);

#endif