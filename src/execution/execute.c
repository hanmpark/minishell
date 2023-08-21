/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/19 23:09:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "signals.h"
#include "exit.h"

#include <sys/wait.h>

extern int	g_sig;

static t_tree	*next_command(t_tree *node)
{
	if (g_sig != 0)
		return (node->or_branch);
	return (node->and_branch);
}

static void	wait_cmds(t_cmd **cmd)
{
	int	status;
	int	i;

	i = -1;
	if (cmd[0]->pid == NO_CHILD_PROCESS)
		return ;
	while (cmd[++i])
		waitpid(cmd[i]->pid, &status, 0);
	set_exit_status(status);
}

static bool	exec_node(t_mnsh *mnsh, t_tree *node)
{
	t_cmd	**cmd;
	int		iostream[2];
	int		i;

	iostream[STDIN_FILENO] = dup(STDIN_FILENO);
	iostream[STDOUT_FILENO] = dup(STDOUT_FILENO);
	cmd = node->cmd;
	i = -1;
	while (++i < node->nb_pipe)
	{
		cmd[i]->pid = parse_exec(mnsh, cmd[i], i, i == node->nb_pipe - 1);
		if (cmd[i]->pid == ERR_RESOURCE)
			return (false);
	}
	reset_iostream(iostream);
	wait_cmds(cmd);
	return (true);
}

/*
* Execute the commands found in the line:
* - the commands are stocked in an AST.
* - depending on the status of the last command,
* it will move on to the and_branch or the or_branch node if they exist.
*/
void	execute(t_mnsh *mnsh, t_tree *node)
{
	while (node)
	{
		if (!exec_node(mnsh, node))
			return ;
		node = next_command(node);
	}
}
