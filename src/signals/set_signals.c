/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:30:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 22:31:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "execution.h"

#include <termios.h>

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

void	set_exit_status(int process_status)
{
	if (process_status == NO_CHILD_PROCESS)
		return ;
	if (WIFEXITED(process_status))
		g_exit = WEXITSTATUS(process_status);
	else if (WIFSIGNALED(process_status))
		g_exit = 128 + WTERMSIG(process_status);
	else if (WIFSTOPPED(process_status))
		g_exit = 128 + WSTOPSIG(process_status);
}
