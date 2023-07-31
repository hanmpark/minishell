#include "minishell.h"
#include "execution.h"
#include "builtins.h"
#include "exit.h"

static bool	find_path_cmd(char **cmd_args, char **envp)
{
	char	**path_cmd;

	path_cmd = define_path_cmd(cmd_args, get_path(envp));
	if (execve(path_cmd[0], path_cmd, envp) == -1)
	{
		ft_arrayfree(path_cmd);
		return (false);
	}
	return (true);
}

static bool	is_path_cmd(char *cmd)
{
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (true);
	return (false);
}

/* 4 possible errors:
* - Command not found
* - No such file or directory
* - Permission denied
* - is a directory
*/
static void	exec_cmd(char **cmd_args, char **envp)
{
	if (!cmd_args)
	{
		g_ms.exit_status = 0;
		exit(EXIT_SUCCESS);
	}
	if (builtin_checker(cmd_args))
		exit(builtin_cmds(cmd_args, envp));
	if (!find_path_cmd(cmd_args, envp))
		if (!is_path_cmd(cmd_args[0]))
			error_not_found(cmd_args[0]);
	if (execve(cmd_args[0], cmd_args, envp) == -1)
		error_not_executable(cmd_args[0]);
}

// Creates a new child process to execute the sent command in it
pid_t	parse_exec(t_cmd **cmd, char **envp, int id, bool is_last)
{
	pid_t	pid;

	if (!is_last && pipe(cmd[id]->pipe) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == CHILD_PROCESS)
	{
		set_iostream(cmd, id, is_last);
		exec_cmd(cmd[id]->args, envp);
	}
	return (pid);
}
