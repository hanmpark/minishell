#ifndef EXECUTION_H
# define EXECUTION_H

# define CHILD_PROCESS 0
# define WRITE_END 1
# define READ_END 0

bool	execute(t_treenode *node, char **envp);
bool	exec_cmd(t_cmd *cmd, char **envp);
bool	exec_last_cmd(t_cmd *cmd, int *status, char **envp);

char	**define_path_to_cmd(char **cmd_args, char *path);
char	*get_path(char **envp);

#endif