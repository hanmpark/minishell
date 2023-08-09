/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/09 15:19:17 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "exit.h"

static t_tree	*next_command(t_tree *node, int cmd_st)
{
	if (cmd_st != NO_CHILD_PROCESS)
	{
		if (WIFEXITED(cmd_st))
			g_exit = WEXITSTATUS(cmd_st);
		else if (WIFSIGNALED(cmd_st))
			g_exit = 128 + WTERMSIG(cmd_st);
		else if (WIFSTOPPED(cmd_st))
			g_exit = 128 + WSTOPSIG(cmd_st);
	}
	if (g_exit != 0)
		return (node->or_branch);
	return (node->and_branch);
}

static void	reset_iostream(int *iostream)
{
	dup2(iostream[STDIN_FILENO], STDIN_FILENO);
	dup2(iostream[STDOUT_FILENO], STDOUT_FILENO);
	close(iostream[STDIN_FILENO]);
	close(iostream[STDOUT_FILENO]);
}

static bool	wait_cmds(t_cmd **cmd, int *cmd_st)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->pid != NO_CHILD_PROCESS)
			waitpid(cmd[i]->pid, cmd_st, 0);
		else
			*cmd_st = NO_CHILD_PROCESS;
	}
	return (true);
}

static bool	exec_node(t_mnsh *mnsh, t_tree *node, int *cmd_st)
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
		if (cmd[i]->pid == FORK_FAIL || cmd[i]->pid == PIPE_FAIL)
			return (false);
	}
	reset_iostream(iostream);
	return (wait_cmds(cmd, cmd_st));
}

/*
* Execute the commands found in the line:
* - the commands are stocked in an AST.
* - depending on the status of the last command,
* it will move on to the and_branch or the or_branch node if they exist.
*/
void	execute(t_mnsh *mnsh, t_tree *node)
{
	int	cmd_st;

	while (node)
	{
		if (!exec_node(mnsh, node, &cmd_st))
			exit(1);
		node = next_command(node, cmd_st);
	}
}
