/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:54:12 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "exit.h"

static t_treenode	*next_command(t_treenode *node, int status)
{
	if (WIFEXITED(status))
		g_ms.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_ms.exit_status = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		g_ms.exit_status = 128 + WSTOPSIG(status);
	if (g_ms.exit_status != 0)
		return (node->or_branch);
	return (node->and_branch);
}

static void	close_pipes(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i + 1])
	{
		close(cmd[i]->pipe[READ_END]);
		close(cmd[i]->pipe[WRITE_END]);
		i++;
	}
}

static bool	exec_node(t_cmd **cmd, int nb_pipe, int *status, char **envp)
{
	int	i;

	i = -1;
	while (++i < nb_pipe)
		cmd[i]->pid = parse_exec(cmd, envp, i, i == nb_pipe - 1);
	close_pipes(cmd);
	i = -1;
	while (cmd[++i])
		waitpid(cmd[i]->pid, status, 0);
	return (true);
}

/* Execute the commands found in the line:
* - the commands are stocked in an AST
* - depending on the status of the last command,
* it will move on to the and_branch or the or_branch node
*/
void	execute(t_treenode *node, char **envp)
{
	int	status;

	while (node)
	{
		exec_node(node->cmd, node->nb_pipe, &status, envp);
		dup2(g_ms.stdin_fileno, STDIN_FILENO);
		node = next_command(node, status);
	}
}
