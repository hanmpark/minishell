/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:14 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/05 01:09:57 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtin.h"
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

/* Execute the cmd:
* - checks if the cmd is a builtin
* - checks if the cmd needs its absolute path
* - checks if it is already an executable
*/
static void	exec_cmd(char **cmd_args, char ***envp)
{
	if (!cmd_args)
		exit(EXIT_SUCCESS);
	if (builtin_checker(cmd_args))
		exit(builtin_cmds(cmd_args, envp));
	if (!find_path_cmd(cmd_args, *envp))
		if (!is_path_cmd(cmd_args[0]))
			error_not_found(cmd_args[0]);
	if (execve(cmd_args[0], cmd_args, *envp) == -1)
		error_not_executable(cmd_args[0]);
}

pid_t	fork_cmd(t_cmd *cmd, char ***envp, bool is_last)
{
	pid_t	pid;

	if (!is_last && pipe(cmd->pipe) == -1)
		return (-1);
	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		set_pipe_output(cmd, is_last);
		exec_cmd(cmd->args, envp);
	}
	set_pipe_input(cmd, is_last);
	return (pid);
}

// Creates a new child process to execute the sent command in it
pid_t	parse_exec(t_cmd *cmd, char ***envp, int id, bool is_last)
{
	set_redirection(cmd);
	if (is_last && id == 0 && builtin_checker(cmd->args))
	{
		g_exit = builtin_cmds(cmd->args, envp);
		return (-1);
	}
	return (fork_cmd(cmd, envp, is_last));
}
