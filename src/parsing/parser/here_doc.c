#include "minishell.h"
#include "parsing.h"
#include "error.h"

static void	check_doc(char *limiter, int *pfd)
{
	char	*new_limiter;
	char	*line;

	close(pfd[0]);
	new_limiter = ft_strjoin(limiter, "\n");
	free(limiter);
	line = readline("> ");
	while (line && ft_strncmp(line, new_limiter, ft_strlen(line)))
	{
		write(pfd[1], line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	free(new_limiter);
	close(pfd[1]);
	exit(EXIT_SUCCESS);
}

int	here_doc(char *limiter)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		check_doc(limiter, pfd);
	close(pfd[1]);
	waitpid(pid, NULL, 0);
	return (pfd[0]);
}
