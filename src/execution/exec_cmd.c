/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:14 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/21 09:47:25 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtin.h"
#include "signals.h"
#include "exit.h"

extern int	g_sig;

static bool	find_path_cmd(char **cmd_args, char **envp)
{
	char	**path_cmd;

	if (!get_path(envp))
		return (false);
	path_cmd = define_path_cmd(cmd_args, get_path(envp));
	if (!path_cmd)
		return (false);
	if (execve(path_cmd[0], path_cmd, envp) == -1)
	{
		ft_arrayfree(path_cmd);
		return (false);
	}
	return (true);
}

static bool	is_path_cmd(char *cmd, char **envp)
{
	if (cmd[ft_strlen(cmd) - 1] == '/')
		return (true);
	else if ((ft_strchr(cmd, '/') && !access(cmd, F_OK)) \
		|| (!ft_strchr(cmd, '/') && !access(cmd, F_OK) && !get_path(envp)))
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
		if (!is_path_cmd(cmd_args[0], *envp))
			error_not_found(cmd_args[0]);
	if (execve(cmd_args[0], cmd_args, *envp) == -1)
		error_not_executable(cmd_args[0]);
}

static pid_t	fork_cmd(t_cmd *cmd, char ***envp, bool is_last)
{
	pid_t	pid;
	int		pfd[2];

	if (!is_last && pipe(pfd) == -1)
	{
		perror("minishell: pipe");
		return (ERR_RESOURCE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (ERR_RESOURCE);
	}
	if (pid == CHILD_PROCESS)
	{
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
		g_sig = builtin_cmds(cmd->args, &mnsh->envp, 1);
		return (NO_CHILD_PROCESS);
	}
	if (cmd->args && (!ft_strncmp(*cmd->args, "./minishell", 11) \
		|| !ft_strncmp(*cmd->args, "minishell", 9)))
		setup_ignore_signals_handlers();
	else
		setup_command_signals_handlers();
	return (fork_cmd(cmd, &mnsh->envp, is_last));
}
