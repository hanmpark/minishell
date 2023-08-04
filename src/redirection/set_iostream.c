/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_iostream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:38 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/05 01:14:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	close_pipes(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i + 1])
	{
		if (cmd[i]->pipe[READ_END] != -1)
			close(cmd[i]->pipe[READ_END]);
		if (cmd[i]->pipe[WRITE_END] != -1)
			close(cmd[i]->pipe[WRITE_END]);
		i++;
	}
}

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

/* Sets the command's input stream:
* if the command is piped to the next command,
* set the pipe's READ_END as the STDIN for the next command
*/
void	set_pipe_input(t_cmd *simple_cmd, bool is_last_cmd)
{
	if (is_last_cmd)
		return ;
	close(simple_cmd->pipe[WRITE_END]);
	dup2(simple_cmd->pipe[READ_END], STDIN_FILENO);
	close(simple_cmd->pipe[READ_END]);
}

/* Sets the command's output stream:
* if the command is piped to the next command,
* writes the command's output into the pipe's WRITE_END
*/
void	set_pipe_output(t_cmd *simple_cmd, bool is_last_cmd)
{
	if (is_last_cmd)
		return ;
	close(simple_cmd->pipe[READ_END]);
	if (simple_cmd->fdout == STDOUT_FILENO)
		dup2(simple_cmd->pipe[WRITE_END], STDOUT_FILENO);
	close(simple_cmd->pipe[WRITE_END]);
}
