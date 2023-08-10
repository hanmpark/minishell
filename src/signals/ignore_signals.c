/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:15:16 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 23:53:53 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

/*
* Sets up signal handlers to ignore the SIGINT and SIGQUIT signals:
* disables the default behavior of these signals, allowing the application
* to continue running normally when these signals are received.
*/
void	setup_ignore_signals_handlers(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
