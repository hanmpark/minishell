#include "minishell.h"
#include "execution.h"
#include "exit.h"

static void	execute_cmd(char **cmd_args, char **envp)
{
	if (!cmd_args)
	{
		g_ms.exit_status = 0;
		exit(EXIT_SUCCESS);
	}
	// have to treat builtins here
	// before executing the command, we have to check if it's a builtin first
	execve(cmd_args[0], cmd_args, envp);
	cmd_args = define_path_to_cmd(cmd_args, get_path(envp));
	if (execve(cmd_args[0], cmd_args, envp) == -1)
		error_exit(g_ms.node, &g_ms.l_token, cmd_args[0], BIN_NOT_FOUND);
}

// Execute the sent command in the child process
static void	treat_child_process(t_cmd **cmd, char **envp, int id, bool is_last)
{
	if (id > 0)
	{
		close(cmd[id - 1]->pipe[WRITE_END]);
		dup2(cmd[id - 1]->pipe[READ_END], STDIN_FILENO);
		close(cmd[id - 1]->pipe[READ_END]);
	}
	set_iostream(cmd[id], is_last);
	execute_cmd(cmd[id]->args, envp);
}

// Creates a new child process to execute the sent command in it
pid_t	exec_cmd(t_cmd **cmd, char **envp, int id, bool is_last)
{
	pid_t	pid;

	if (!is_last && pipe(cmd[id]->pipe) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == CHILD_PROCESS)
		treat_child_process(cmd, envp, id, is_last);
	return (pid);
}
