#ifndef EXECUTION_H
# define EXECUTION_H

# define CHILD_PROCESS 0
# define WRITE_END 1
# define READ_END 0

void	execute(t_treenode *node, char ***envp);
pid_t	parse_exec(t_cmd *cmd, char ***envp, int id, bool is_last);
void	set_redirection(t_cmd *cmd);
void	set_pipe_input(t_cmd *simple_cmd, bool is_last_cmd);
void	set_pipe_output(t_cmd *simple_cmd, bool is_last_cmd);
void	close_pipes(t_cmd **cmd);

char	**define_path_cmd(char **cmd_args, char *path);
char	*get_path(char **envp);

#endif