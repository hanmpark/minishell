#ifndef EXECUTION_H
# define EXECUTION_H

# define CHILD_PROCESS 0
# define WRITE_END 1
# define READ_END 0

void	execute(t_treenode *node, char **envp);
pid_t	exec_cmd(t_cmd **cmd, char **envp, int id, bool is_last);

char	**define_path_to_cmd(char **cmd_args, char *path);
char	*get_path(char **envp);
void	set_iostream(t_cmd **cmd, int id, bool is_last);

#endif