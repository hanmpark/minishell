/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:10:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 21:12:52 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

static void	basic_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 1;
}

static void	basic_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

void	basic_signals(void)
{
	signal(SIGINT, basic_sigint);
	signal(SIGQUIT, basic_sigquit);
}
