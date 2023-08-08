/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:08 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:18:10 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	builtin_checker(char **cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

// check for each builtin commands
int	builtin_cmds(char **cmd, char ***envp, pid_t pid)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, *envp));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, envp));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, envp));
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(*envp));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(pid, cmd));
	return (0);
}
