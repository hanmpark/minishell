/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iostream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:38 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 14:47:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

/*
* Sets the command's I/O stream when a redirection is encountered:
* if the command contains opened file descriptor(s), sets them
* as the STDIN/STDOUT.
*/
void	set_redirection(t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
}

/*
* Sets the command's input stream:
* if the command is piped to the next command,
* set the pipe's READ_END as the STDIN for the next command.
*/
void	set_pipe_input(int *pfd, bool is_last_cmd)
{
	if (is_last_cmd)
		return ;
	close(pfd[WRITE_END]);
	dup2(pfd[READ_END], STDIN_FILENO);
	close(pfd[READ_END]);
}

/*
* Sets the command's output stream:
* if the command is piped to the next command,
* writes the command's output into the pipe's WRITE_END.
*/
void	set_pipe_output(int fdout, int *pfd, bool is_last_cmd)
{
	if (is_last_cmd)
		return ;
	close(pfd[READ_END]);
	if (fdout == STDOUT_FILENO)
		dup2(pfd[WRITE_END], STDOUT_FILENO);
	close(pfd[WRITE_END]);
}

void	reset_iostream(int *iostream)
{
	dup2(iostream[STDIN_FILENO], STDIN_FILENO);
	dup2(iostream[STDOUT_FILENO], STDOUT_FILENO);
	close(iostream[STDIN_FILENO]);
	close(iostream[STDOUT_FILENO]);
}
