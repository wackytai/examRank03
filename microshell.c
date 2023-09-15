#include "microshell.h"

int	error_message(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
		write(STDERR_FILENO, &s1[i], 1);
	i = -1;
	if (s2)
		while (s2[++i])
			write(STDERR_FILENO, &s2[i], 1);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	ft_cd(char **argv, int i)
{
	int	flag;

	if (i != 2)
		return (error_message("error: cd: bad arguments", 0));
	flag = chdir(argv[1]);
	if (flag == -1)
		return (error_message("error: cd: cannot change directory to ", argv[1]));
	return (0);
}

int	ft_executer(char **argv, int i, char **envp)
{
	pid_t	pid;
	int		is_pipe;
	int		status;
	int		fd[2];

	is_pipe = 0;
	if (argv[i] && !strcmp(argv[i], "|"))
		is_pipe = 1;
	if (is_pipe && pipe(fd) == -1)
		exit (error_message("error: fatal", 0));
	pid = fork();
	if (pid == -1)
		exit (error_message("error: fatal", 0));
	if (!pid)
	{
		argv[i] = 0;
		if (is_pipe && (dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[0] == -1)
				|| close(fd[1] == -1)))
			exit (error_message("error: fatal", 0));
		execve(*argv, argv, envp);
		exit (error_message("error: cannot execute ", *argv));
	}
	waitpid(pid, &status, 0);
	if (is_pipe && (dup2(fd[0], STDIN_FILENO) == -1 || close(fd[0] == -1)
			|| close(fd[1] == -1)))
		exit (error_message("error: fatal", 0));
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
