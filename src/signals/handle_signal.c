/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:40:22 by kquetat-          #+#    #+#             */
/*   Updated: 2023/08/10 13:56:53 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "signals.h"

void	set_exit_status(int process_status)
{
	if (WIFEXITED(process_status))
		g_exit = WEXITSTATUS(process_status);
	else if (WIFSIGNALED(process_status))
		g_exit = 128 + WTERMSIG(process_status);
	else if (WIFSTOPPED(process_status))
		g_exit = 128 + WSTOPSIG(process_status);
}

void	basic_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 1;
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(1);
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	command_signals(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	handle_signals(struct sigaction *sa, void (*f)(int))
{
	ft_bzero(sa, sizeof(struct sigaction));
	if (f != NULL)
		sa->sa_handler = f;
	sa->sa_flags = 0;
	sigemptyset(&(sa->sa_mask));
	if (sigaction(SIGINT, sa, 0) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, sa, 0) == -1)
		exit(EXIT_FAILURE);
}
