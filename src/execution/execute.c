#include "minishell.h"
#include "execution.h"
#include "error.h"

/* Returns the PATH variable in envp as a string */
char	*define_path(char **envp)
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

/* Looks for the command's path and returns it (if found) as a string */
char	*define_cmdpath(char *cmd, char *env_path)
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
			ft_freestr_array(cmd_paths);
			return (right_path);
		}
		free(right_path);
		i++;
	}
	ft_freestr_array(cmd_paths);
	return (NULL);
}

/* Defines the cmd_args */
char	**define_cmdargs(char **cmd_args, char *path)
{
	char	*cmd_path;

	cmd_path = define_cmdpath(cmd_args[0], path);
	if (cmd_path == NULL)
		return (cmd_args);
	free(cmd_args[0]);
	cmd_args[0] = cmd_path;
	return (cmd_args);
}

// Execute the sent command in the child process
static void	child_process(t_cmd *cmd, char **envp, int *pfd)
{
	close(pfd[READ_END]);
	dup2(pfd[WRITE_END], STDOUT_FILENO);
	close(pfd[WRITE_END]);
	if (!cmd->args)
	{
		g_ms.return_value = 0;
		exit(EXIT_SUCCESS);
	}
	// builtins first
	execve(cmd->args[0], cmd->args, envp);
	cmd->args = define_cmdargs(cmd->args[0], define_path(envp));
	if (execve(cmd->args[0], cmd->args, envp) == -1)
		ft_arrayfree(cmd->args);
}

static void	set_infile(t_cmd *cmd)
{
	dup2(cmd->fdin, STDIN_FILENO);
	close(cmd->fdin);
}

// Creates a new child process to execute the sent command in it
static bool	create_process(t_cmd *cmd, char **envp)
{
	int	pid;
	int	pfd[2];

	if (pipe(pfd) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == CHILD_PROCESS)
		child_process(cmd, envp, pfd);
	close(pfd[WRITE_END]);
	dup2(pfd[READ_END], STDIN_FILENO);
	close(pfd[READ_END]);
	return (true);
}

static bool	exec_node(t_cmd **cmd, int nb_pipe, char **envp)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		set_infile(cmd[i]);
		if (!create_process(cmd[i], envp))
			return (false);
		i++;
	}
	return (true);
}

// Execute the commands
bool	execute(t_treenode *node, char **envp)
{
	while (node)
	{
		if (!exec_node(node->cmd, node->nb_pipe, envp))
			return (false);
		// check if we have to go in the or_branch or and_branch
	}
	return (true);
}
