/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:40:22 by kquetat-          #+#    #+#             */
/*   Updated: 2023/08/10 09:13:31 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

void	command_signals(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (signal == SIGQUIT)
		return ;
}

void	handle_signals(struct sigaction *sa, void (*f)(int))
{
	ft_bzero(sa, sizeof(struct sigaction));
	sa->sa_handler = f;
	sa->sa_flags = 0;
	sigemptyset(&(sa->sa_mask));
	if (sigaction(SIGINT, sa, 0) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, sa, 0) == -1)
		exit(EXIT_FAILURE);
}
