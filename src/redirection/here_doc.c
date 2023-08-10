/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:42 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 13:33:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "signals.h"

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

static char	*expand_here_doc(t_mnsh *mnsh, bool is_quoted, char *line)
{
	if (!is_quoted)
		return (treat_env(mnsh, line, false));
	return (line);
}

static void	init_here_doc(t_mnsh *mnsh, char *token, bool is_quoted, int *pfd)
{
	char	*limiter;
	char	*line;
	char	*line_nl;

	close(pfd[0]);
	limiter = format_limiter(token);
	line = readline("> ");
	while (line && ft_strcmp(line, limiter))
	{
		line = expand_here_doc(mnsh, is_quoted, line);
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

/*
* Here document ('<<'):
* - passes the input(s) to a command as if it were read from a file.
* - creates a new process to handle the input and waits for the user's input
* until the specified limiter is found. Once the limiter is encountered,
* the process finishes writing the input, and the command proceeds.
*/
int	here_doc(t_mnsh *mnsh, char *token)
{
	int	pfd[2];
	int	pid;
	int	status;

	handle_signals(mnsh->sa, SIG_IGN);
	if (pipe(pfd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_termios(true);
		handle_signals(mnsh->sa, &heredoc_signals);
		init_here_doc(mnsh, token, found_quote(token), pfd);
	}
	close(pfd[1]);
	waitpid(pid, &status, 0);
	set_exit_status(status);
	if (g_exit != 0)
	{
		close(pfd[0]);
		g_exit = 1;
		return (-2);
	}
	return (pfd[0]);
}
