/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:16:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 22:42:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	set_termios(bool set);

void	basic_signals(void);
void	command_signals(void);
void	heredoc_signals(void);
void	ignore_signals(void);
void	set_exit_status(int process_status);

#endif