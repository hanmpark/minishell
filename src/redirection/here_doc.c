/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:42 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/15 20:05:27 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "signals.h"

#include <sys/wait.h>

extern int	g_sig;

static bool	should_expand(char *token)
{
	while (*token)
	{
		if (*token == '\'' || *token == '"')
			return (false);
		token++;
	}
	return (true);
}

static char	*expand_here_doc(t_mnsh *mnsh, bool expand, char *line)
{
	if (expand)
		return (treat_env(mnsh, line, false));
	return (line);
}

static void	init_here_doc(t_mnsh *mnsh, char *limiter, bool expand, int *pfd)
{
	char	*line;
	char	*line_nl;

	setup_heredoc_signals_handlers();
	set_termios(true);
	close(pfd[0]);
	line = readline("> ");
	while (line && ft_strcmp(line, limiter))
	{
		line = expand_here_doc(mnsh, expand, line);
		line_nl = ft_strjoin(line, "\n");
		write(pfd[1], line_nl, ft_strlen(line_nl));
		free(line);
		free(line_nl);
		line = readline("> ");
	}
	if (line)
		free(line);
	free(limiter);
	close(pfd[1]);
	exit(EXIT_SUCCESS);
}

static int	check_here_doc_state(int pfd, pid_t pid)
{
	int	here_doc_status;

	waitpid(pid, &here_doc_status, 0);
	set_exit_status(here_doc_status);
	if (g_sig != 0)
	{
		close(pfd);
		g_sig = 1;
		return (-2);
	}
	return (pfd);
}

/*
* Here document ('<<'):
* - passes the input(s) to a command as if it were read from a file.
* - creates a new process to handle the input and waits for the user's input
* until the specified limiter is found. Once the limiter is encountered,
* the process finishes writing the input, and the command proceeds.
*/
int	here_doc(t_mnsh *mnsh, char *token)
{
	pid_t	pid;
	int		pfd[2];

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pfd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		init_here_doc(mnsh, format_limiter(token), should_expand(token), pfd);
	close(pfd[1]);
	return (check_here_doc_state(pfd[0], pid));
}
