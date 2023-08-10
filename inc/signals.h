/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:16:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 23:10:33 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	set_termios(bool set);

void	setup_basic_signals_handlers(void);
void	setup_command_signals_handlers(void);
void	setup_heredoc_signals_handlers(void);
void	setup_ignore_signals_handlers(void);
void	set_exit_status(int process_status);

#endif