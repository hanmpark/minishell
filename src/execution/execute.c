/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 23:59:24 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "signals.h"
#include "exit.h"

extern int	g_exit;

static t_tree	*next_command(t_tree *node)
{
	if (g_exit != 0)
		return (node->or_branch);
	return (node->and_branch);
}

static void	wait_cmds(t_cmd **cmd)
{
	int	status;
	int	i;

	i = -1;
	status = NO_CHILD_PROCESS;
	while (cmd[++i])
	{
		if (cmd[i]->pid != NO_CHILD_PROCESS)
			waitpid(cmd[i]->pid, &status, 0);
	}
	set_exit_status(status);
}

static void	exec_node(t_mnsh *mnsh, t_tree *node)
{
	t_cmd	**cmd;
	int		iostream[2];
	int		i;

	iostream[STDIN_FILENO] = dup(STDIN_FILENO);
	iostream[STDOUT_FILENO] = dup(STDOUT_FILENO);
	cmd = node->cmd;
	i = -1;
	while (++i < node->nb_pipe)
		cmd[i]->pid = parse_exec(mnsh, cmd[i], i, i == node->nb_pipe - 1);
	reset_iostream(iostream);
	return (wait_cmds(cmd));
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
		exec_node(mnsh, node);
		node = next_command(node);
	}
}
