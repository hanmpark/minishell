/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:40:22 by kquetat-          #+#    #+#             */
/*   Updated: 2023/08/09 20:06:16 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	parent_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("PASS\n");
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// else if (signal == SIGQUIT)
	// 	return ;
}

static void	child_sig_handler(int signal, siginfo_t *sa, void *ignore)
{
	(void)ignore;
	if (signal == SIGINT)
		kill(sa->si_pid, SIGTERM);
}

void	handle_sig_child(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &child_sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(sa.sa_mask));
	if (sigaction(SIGINT, &sa, 0) == -1)
		exit(EXIT_FAILURE);
}

void	handle_sig_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = &parent_sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	if (sigaction(SIGINT, &sa, 0) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		exit(EXIT_FAILURE);
}
