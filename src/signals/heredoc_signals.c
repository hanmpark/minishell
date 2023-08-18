/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:06:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/18 15:19:47 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "putft.h"

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

/*
* Sets up custom signal handlers for the SIGINT and SIGQUIT signals:
* - specifically during the input collection phase of a heredoc.
* - it provides tailored behavior for handling interruptions and termination
* signals while gathering input for a heredoc.
*/
void	setup_heredoc_signals_handlers(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, heredoc_sigquit);
}
