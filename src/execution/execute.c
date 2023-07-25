#include "minishell.h"
#include "execution.h"
#include "error.h"

// Execute the sent command in the child process
static void	child_process(t_cmd *cmd, char **envp, int *pfd)
{
	close(pfd[READ_END]);
	if (cmd->fdout != STDOUT_FILENO)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
	}
	else
		dup2(pfd[WRITE_END], STDOUT_FILENO);
	close(pfd[WRITE_END]);
	if (!cmd->args)
	{
		g_ms.return_value = 0;
		exit(EXIT_SUCCESS);
	}
	// builtins first
	execve(cmd->args[0], cmd->args, envp);
	cmd->args = define_path_to_cmd(cmd->args, get_path(envp));
	if (execve(cmd->args[0], cmd->args, envp) == -1)
		error_exit(g_ms.node, &g_ms.l_token, cmd->args[0]);
}

/* Creates a new child process to execute the last command */
static bool	last_process(t_cmd *cmd, int *status, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == CHILD_PROCESS)
	{
		if (cmd->fdout != STDOUT_FILENO)
		{
			dup2(cmd->fdout, STDOUT_FILENO);
			close(cmd->fdout);
		}
		if (!cmd->args)
		{
			g_ms.return_value = 0;
			exit(EXIT_SUCCESS);
		}
		execve(cmd->args[0], cmd->args, envp);
		cmd->args = define_path_to_cmd(cmd->args, get_path(envp));
		if (execve(cmd->args[0], cmd->args, envp) == -1)
			error_exit(g_ms.node, &g_ms.l_token, cmd->args[0]);
	}
	waitpid(pid, status, 0);
	return (true);
}

// Creates a new child process to execute the sent command in it
static bool	create_process(t_cmd *cmd, char **envp)
{
	int	pid;
	int	pfd[2];

	if (pipe(pfd) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == CHILD_PROCESS)
		child_process(cmd, envp, pfd);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	else
		dup2(pfd[READ_END], STDIN_FILENO);
	close(pfd[WRITE_END]);
	close(pfd[READ_END]);
	return (true);
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
		if (i < nb_pipe - 1 && !create_process(cmd[i], envp))
			return (false);
		if (i == nb_pipe - 1 && !last_process(cmd[i], status, envp))
			return (false);
		dup2(g_ms.stdin_fileno, STDIN_FILENO);
		dup2(g_ms.stdout_fileno, STDOUT_FILENO);
		i++;
	}
	return (true);
}

static t_treenode	*next_command(t_treenode *node, int status)
{
	if (WIFEXITED(status))
		g_ms.return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_ms.return_value = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		g_ms.return_value = 128 + WSTOPSIG(status);
	if (g_ms.return_value != 0)
		return (node->or_branch);
	return (node->and_branch);
}

// Execute the commands
bool	execute(t_treenode *node, char **envp)
{
	int	status;

	while (node)
	{
		exec_node(node->cmd, node->nb_pipe, &status, envp);
		node = next_command(node, status);
	}
	return (true);
}
