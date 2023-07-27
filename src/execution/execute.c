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

static bool	exec_node(t_cmd **cmd, int nb_pipe, int *status, char **envp)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (cmd[i]->fdin != STDIN_FILENO)
		{
			dup2(cmd[i]->fdin, STDIN_FILENO);
			close(cmd[i]->fdin);
		}
		if (i < nb_pipe - 1 && !exec_cmd(cmd[i], envp))
			return (false);
		if (i == nb_pipe - 1 && !exec_last_cmd(cmd[i], status, envp))
			return (false);
		dup2(g_ms.stdout_fileno, STDOUT_FILENO);
		i++;
	}
	return (true);
}

/* Execute the commands found in the line:
* - the commands are stocked in an AST
* - depending on the status of the last command,
* it will move on to the and_branch or the or_branch node
*/
bool	execute(t_treenode *node, char **envp)
{
	int	status;

	while (node)
	{
		exec_node(node->cmd, node->nb_pipe, &status, envp);
		dup2(g_ms.stdin_fileno, STDIN_FILENO);
		node = next_command(node, status);
	}
	return (true);
}
