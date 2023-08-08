/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:40:22 by kquetat-          #+#    #+#             */
/*   Updated: 2023/08/08 23:40:23 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		g_sig = 2;
	if (signal == SIGQUIT)
		g_sig = 3;
}

void	interaction_mod(void)
{
	if (g_sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line();
		rl_redisplay();
		g_sig = 0;
	}
}

void	handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, 0) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		exit(EXIT_FAILURE);
}
