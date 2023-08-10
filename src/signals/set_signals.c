/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:30:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 15:20:18 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

#include <termios.h>

void	set_termios(bool set)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	if (set == true)
		termios.c_lflag &= ~(ICANON | ECHOCTL);
	else
		termios.c_lflag |= ICANON | ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

void	set_exit_status(int process_status)
{
	if (WIFEXITED(process_status))
		g_exit = WEXITSTATUS(process_status);
	else if (WIFSIGNALED(process_status))
		g_exit = 128 + WTERMSIG(process_status);
	else if (WIFSTOPPED(process_status))
		g_exit = 128 + WSTOPSIG(process_status);
}
