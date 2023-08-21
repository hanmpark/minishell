/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 23:10:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/21 10:00:54 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "putft.h"

extern int	g_sig;

static void	basic_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 1;
}

static void	basic_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

/*
* Sets up the basic signal handlers for the SIGINT and SIGQUIT signals:
* it provides a simple behavior for these signals, allowing interruption
* of the ongoing operation (SIGINT) and graceful termination
* with core dump (SIGQUIT).
*/
void	setup_basic_signals_handlers(void)
{
	signal(SIGINT, basic_sigint);
	signal(SIGQUIT, basic_sigquit);
}
