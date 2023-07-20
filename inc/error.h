#ifndef ERROR_H
# define ERROR_H

# define ERR_QUOTE "minishell: syntax error expected closing `"
# define ERR_TOKEN "minishell: syntax error near unexpected token `"
# define ERR_NOHANDLE "minishell: undefined token `"
# define ERR_CTOKEN "'\n"
# define ERR_REDIR "minishell: syntax error near unexpected token `newline'\n"

# define ERR_AMB ": ambiguous redirect\n"
# define ERR_ENOENT ": No such file or directory\n"

# define ERR_MISS "minishell: syntax error missing token\n"

bool	error_token(char *token, bool handle);
char	*error_quote(t_type type);
bool	error_parsing(char *msg);
void	error_exit(t_treenode *tree, t_token **l_token, char *msg);
bool	error_expand(char *error_token, char *ms, int error_code);

void	free_tree(t_treenode *tree);
void	free_node(t_treenode **node);
void	free_cmd(t_cmd **cmd);

#endif