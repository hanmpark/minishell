/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iostream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:38 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:52:40 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

static bool	set_redirection(t_cmd *cmd)
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
		return (true);
	}
	return (false);
}

/* Sets the I/O stream for the next command:
* - if there is/are redirection(s) in the command line, sets them in priority
* - else sets the pipe as the I/O stream
* - the last command is not piped
*/
void	set_iostream(t_cmd **cmd, int id, bool is_last)
{
	if (id > 0)
	{
		close(cmd[id - 1]->pipe[WRITE_END]);
		dup2(cmd[id - 1]->pipe[READ_END], STDIN_FILENO);
		close(cmd[id - 1]->pipe[READ_END]);
	}
	if (!is_last)
		close(cmd[id]->pipe[READ_END]);
	if (!set_redirection(cmd[id]) && !is_last)
		dup2(cmd[id]->pipe[WRITE_END], STDOUT_FILENO);
	if (!is_last)
		close(cmd[id]->pipe[WRITE_END]);
}
