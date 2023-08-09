/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:14 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/09 20:07:04 by kquetat-         ###   ########.fr       */
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
	if (execve(path_cmd[0], path_cmd, envp) == EXEC_FAIL)
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

/*
* Executes the command:
* - checks if the command is a builtin.
* - checks if the command needs its absolute path.
* - checks if the command is already an executable.
*/
static void	exec_cmd(char **cmd_args, char ***envp)
{
	if (!cmd_args)
		exit(EXIT_SUCCESS);
	if (builtin_checker(cmd_args))
		exit(builtin_cmds(cmd_args, envp, CHILD_PROCESS));
	if (!find_path_cmd(cmd_args, *envp))
		if (!is_path_cmd(cmd_args[0]))
			error_not_found(cmd_args[0]);
	if (execve(cmd_args[0], cmd_args, *envp) == EXEC_FAIL)
		error_not_executable(cmd_args[0]);
}

pid_t	fork_cmd(t_cmd *cmd, char ***envp, bool is_last)
{
	pid_t	pid;
	int		pfd[2];

	if (!is_last && pipe(pfd) == PIPE_FAIL)
	{
		perror("minishell: pipe");
		return (PIPE_FAIL);
	}
	pid = fork();
	if (pid == FORK_FAIL)
	{
		perror("minishell: fork");
		return (FORK_FAIL);
	}
	if (pid == CHILD_PROCESS)
	{
		handle_sig_child();
		set_pipe_output(cmd->fdout, pfd, is_last);
		exec_cmd(cmd->args, envp);
	}
	set_pipe_input(pfd, is_last);
	return (pid);
}

/*
* Executes a pipeline:
* - executes the given command either as a built-in command
* or in a new child process.
* - manages input/output redirection if needed.
*/
pid_t	parse_exec(t_mnsh *mnsh, t_cmd *cmd, int id, bool is_last)
{
	set_redirection(cmd);
	if (is_last && id == 0 && builtin_checker(cmd->args))
	{
		g_exit = builtin_cmds(cmd->args, &mnsh->envp, 1);
		return (NO_CHILD_PROCESS);
	}
	return (fork_cmd(cmd, &mnsh->envp, is_last));
}
