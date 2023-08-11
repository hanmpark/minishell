/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:30:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 18:41:25 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "execution.h"

#include <termios.h>

extern int	g_sig;

void	set_termios(bool set)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	if (set == true)
		termios.c_lflag &= ~ECHOCTL;
	else
		termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

/*
* Updates the global exit status based on the status of a child process:
* - it interprets the process status, which includes information about
* whether the process exited normally, was terminated by a signal,
* or was stopped.
* - the global exit status is updated accordingly to reflect
* the outcome of the process.
*/
void	set_exit_status(int process_status)
{
	if (WIFEXITED(process_status))
		g_sig = WEXITSTATUS(process_status);
	else if (WIFSIGNALED(process_status))
		g_sig = 128 + WTERMSIG(process_status);
	else if (WIFSTOPPED(process_status))
		g_sig = 128 + WSTOPSIG(process_status);
}
