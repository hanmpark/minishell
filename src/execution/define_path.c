/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:21 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:54:23 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "exit.h"

// Returns the PATH variable in envp as a string
char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

// Looks for the command's path and returns it as a string
static char	*find_right_path(char *cmd, char *env_path)
{
	char	**cmd_paths;
	char	*right_path;
	char	*dir_path;
	int		i;

	cmd_paths = ft_split(env_path + 5, ':');
	i = 0;
	while (cmd_paths[i])
	{
		dir_path = ft_strjoin(cmd_paths[i], "/");
		right_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(right_path, F_OK) == 0)
		{
			ft_arrayfree(cmd_paths);
			return (right_path);
		}
		free(right_path);
		i++;
	}
	ft_arrayfree(cmd_paths);
	return (NULL);
}

// Defines the absolute path to the cmd
char	**define_path_cmd(char **cmd_args, char *paths)
{
	char	**path_defined_cmd;
	char	*right_path;

	right_path = find_right_path(cmd_args[0], paths);
	if (right_path == NULL)
		return (ft_arraydup(cmd_args));
	path_defined_cmd = ft_arraydup(cmd_args);
	free(path_defined_cmd[0]);
	path_defined_cmd[0] = right_path;
	return (path_defined_cmd);
}
