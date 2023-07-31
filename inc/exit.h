#ifndef EXIT_H
# define EXIT_H

# define ERR_QUOTE "minishell: syntax error expected closing `"
# define ERR_TOKEN "minishell: syntax error near unexpected token `"
# define ERR_NOHANDLE "minishell: undefined token `"
# define ERR_CTOKEN "'\n"

# define ERR_AMB ": ambiguous redirect\n"
# define ERR_NOTFOUND ": command not found\n"
# define ERR_ENOENT ": No such file or directory\n"
# define ERR_PERM ": Permission denied\n"
# define ERR_ISDIR ": is a directory\n"

# define ERR_REDIR "minishell: syntax error near unexpected token `newline"
# define ERR_MISS "minishell: syntax error missing token\n"

# define NO_HANDLE 1
# define NOT_EXECUTABLE 126
# define BIN_NOT_FOUND 127
# define ORDER_WRONG 258

bool	error_token(char *token, char *err_msg, int st);
void	error_exit(char *err_src, char *msg, int st);
void	error_not_found(char *cmd);
void	error_not_executable(char *cmd);

void	free_tokens(t_token **l_token);
void	free_tree(t_treenode *tree);
void	free_cmd(t_cmd **cmd);

#endif