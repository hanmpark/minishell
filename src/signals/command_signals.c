/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:13:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:50:04 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "putft.h"

static void	command_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	command_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

/*
* Sets up custom signal handlers for the SIGINT and SIGQUIT signals
* - within the context of a specific command.
* - provides specialized behavior to handle interruptions and termination
* signals during the execution of a command.
*/
void	setup_command_signals_handlers(void)
{
	signal(SIGINT, command_sigint);
	signal(SIGQUIT, command_sigquit);
}
