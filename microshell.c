/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:45:37 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/12 14:53:05 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	error_message(char *str, char *s1)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
	i = -1;
	if (s1)
		while (s1[++i])
			write(STDERR_FILENO, &s1[i], 1);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	ft_cd(char **argv, int i)
{
	int	flag;

	if (i != 2)
		return (error_message("error: cd: bad arguments\n", 0));
	flag = chdir(argv[1]);
	if (flag)
		return (error_message("error: cd: cannot change directory to ", argv[1]));
	return (0);
}

int	ft_executer(char **argv, int i, char **envp)
{
	int	pipe_fd[2];
	int	status;
	int	pid;

	if (argv[i] && !strcmp(argv[i], "|") && pipe(pipe_fd))
		error_message("error: fatal", 0);
	pid = fork();
	if (!pid)
	{
		if (argv[i] && !strcmp(argv[i], "|") && (dup2(pipe_fd[1], STDOUT_FILENO) == -1
				|| close(pipe_fd[0] == -1 || close(pipe_fd[1] == -1))))
			return (error_message("error: fatal", 0));
	}
	waitpid(pid, &status, 0);
	if (argv[i] && !strcmp(argv[i], "|") && (dup2(pipe_fd[0], STDIN_FILENO) == -1
			|| close(pipe_fd[0] == -1 || close(pipe_fd[1] == -1))))
		return (error_message("error: fatal", 0));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (argc < 2)
		return (status);
	while (argv[i] && argv[++i])
	{
		argv += i;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (!strcmp(*argv, "cd"))
			status = ft_cd(argv, i);
		else if (i)
			status = ft_executer(argv, i, envp);
	}
	return (status);
}
