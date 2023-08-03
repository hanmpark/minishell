#include "minishell.h"
#include "builtin.h"

int	builtin_checker(char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	return (ft_unset(cmd));
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	return (ft_env(cmd, envp));
	// else if (!ft_strcmp(cmd[0], "exit"))
	// 	return (ft_exit(cmd));
	return (0);
}

// check for each builtin commands
int	builtin_cmds(char **cmd, char **envp)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd[0], "export"))
	 	return (ft_export(cmd, envp));
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	return (ft_unset(cmd));
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	return (ft_env(cmd, envp));
	// else if (!ft_strcmp(cmd[0], "exit"))
	// 	return (ft_exit(cmd));
	return (0);
}
