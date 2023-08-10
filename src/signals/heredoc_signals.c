/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:06:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 21:10:13 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

static void	heredoc_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(1);
}

static void	heredoc_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, heredoc_sigquit);
}
