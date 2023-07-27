#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "exit.h"

static bool	found_quote(char *line)
{
	while (*line)
	{
		if (*line == '\'' || *line == '"')
			return (true);
		line++;
	}
	return (false);
}

static char	*expand_here_doc(bool is_quote, char *line)
{
	if (!is_quote)
		return (treat_env(line));
	return (line);
}

static void	check_doc(char *limiter, int *pfd)
{
	char	*line;

	close(pfd[0]);
	line = readline("> ");
	while (line && ft_strncmp(line, limiter, ft_strlen(line)))
	{
		line = expand_here_doc(found_quote(line), line);
		write(pfd[1], line, ft_strlen(line));
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	free(limiter);
	close(pfd[1]);
	exit(EXIT_SUCCESS);
}

/* Here document which is symbolised by the '<<' token
* - creates a new process to write the input into a pipe
* - waits for the user's input until the limiter is found
*/
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
		check_doc(ft_strjoin(limiter, "\n"), pfd);
	close(pfd[1]);
	waitpid(pid, NULL, 0);
	return (pfd[0]);
}
