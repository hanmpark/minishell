/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/05 01:12:34 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "exit.h"

static t_treenode	*next_command(t_treenode *node, int status)
{
	if (status != -1)
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

static bool	exec_node(t_cmd **cmd, int nb_pipe, int *status, char ***envp)
{
	int	stdin_fileno;
	int	stdout_fileno;
	int	i;

	stdin_fileno = dup(STDIN_FILENO);
	stdout_fileno = dup(STDOUT_FILENO);
	i = -1;
	while (++i < nb_pipe)
		cmd[i]->pid = parse_exec(cmd[i], envp, i, i == nb_pipe - 1);
	close_pipes(cmd);
	dup2(stdin_fileno, STDIN_FILENO);
	dup2(stdout_fileno, STDOUT_FILENO);
	close(stdin_fileno);
	close(stdout_fileno);
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->pid != -1)
			waitpid(cmd[i]->pid, status, 0);
		else
			*status = -1;
	}
	return (true);
}

/* Execute the commands found in the line:
* - the commands are stocked in an AST
* - depending on the status of the last command,
* it will move on to the and_branch or the or_branch node
*/
void	execute(t_treenode *node, char ***envp)
{
	int	status;

	while (node)
	{
		exec_node(node->cmd, node->nb_pipe, &status, envp);
		node = next_command(node, status);
	}
}
