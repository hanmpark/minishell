#include "minishell.h"
#include "execution.h"
#include "error.h"

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

// Looks for the command's path and returns it (if found) as a string
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
		if (access(right_path, F_OK | X_OK) == 0)
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
char	**define_path_to_cmd(char **cmd_args, char *path)
{
	char	*cmd_path;

	cmd_path = find_right_path(cmd_args[0], path);
	if (cmd_path == NULL)
		return (cmd_args);
	free(cmd_args[0]);
	cmd_args[0] = cmd_path;
	return (cmd_args);
}
