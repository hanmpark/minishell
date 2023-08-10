/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:16:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 14:32:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	set_termios(bool set);

void	handle_signals(struct sigaction *sa, void (*f)(int));
void	command_signals(int signal);
void	heredoc_signals(int signal);
void	basic_signals(int signal);
void	set_exit_status(int process_status);

#endif