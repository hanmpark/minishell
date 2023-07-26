#include "minishell.h"
#include "execution.h"
#include "error.h"

static void	execute_cmd(char **cmd, char **envp)
{
	if (!cmd)
	{
		g_ms.return_value = 0;
		exit(EXIT_SUCCESS);
	}
	// have to treat builtins here
	// before executing the command, we have to check if it's a builtin first
	execve(cmd[0], cmd, envp);
	cmd = define_path_to_cmd(cmd, get_path(envp));
	if (execve(cmd[0], cmd, envp) == -1)
		error_exit(g_ms.node, &g_ms.l_token, cmd[0]);
}

// Execute the sent command in the child process
static void	treat_child_process(t_cmd *cmd, char **envp, int *pfd)
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
	execute_cmd(cmd->args, envp);
}

// Creates a new child process to execute the last command
bool	exec_last_cmd(t_cmd *cmd, int *status, char **envp)
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
		execute_cmd(cmd->args, envp);
	}
	waitpid(pid, status, 0);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	return (true);
}

// Creates a new child process to execute the sent command in it
bool	exec_cmd(t_cmd *cmd, char **envp)
{
	int	pid;
	int	pfd[2];

	if (pipe(pfd) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == CHILD_PROCESS)
		treat_child_process(cmd, envp, pfd);
	if (cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	else
		dup2(pfd[READ_END], STDIN_FILENO);
	close(pfd[WRITE_END]);
	close(pfd[READ_END]);
	return (true);
}
