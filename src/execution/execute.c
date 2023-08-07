/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 07:52:04 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "exit.h"

static t_treenode	*next_command(t_treenode *node, int status)
{
	if (status != NO_CHILD_PROCESS)
	{
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
		else if (WIFSTOPPED(status))
			g_exit = 128 + WSTOPSIG(status);
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

static bool	exec_node(t_cmd **cmd, int nb_pipe, int *status, char ***envp)
{
	int	iostream[2];
	int	i;

	iostream[STDIN_FILENO] = dup(STDIN_FILENO);
	iostream[STDOUT_FILENO] = dup(STDOUT_FILENO);
	i = -1;
	while (++i < nb_pipe)
	{
		cmd[i]->pid = parse_exec(cmd[i], envp, i, i == nb_pipe - 1);
		if (cmd[i]->pid == FORK_FAIL || cmd[i]->pid == PIPE_FAIL)
			return (false);
	}
	reset_iostream(iostream);
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->pid != NO_CHILD_PROCESS)
			waitpid(cmd[i]->pid, status, 0);
		else
			*status = NO_CHILD_PROCESS;
	}
	return (true);
}

/*
* Execute the commands found in the line:
* - the commands are stocked in an AST.
* - depending on the status of the last command,
* it will move on to the and_branch or the or_branch node if they exist.
*/
void	execute(t_treenode *node, char ***envp)
{
	int	status;

	while (node)
	{
		if (!exec_node(node->cmd, node->nb_pipe, &status, envp))
			exit(1);
		node = next_command(node, status);
	}
}
