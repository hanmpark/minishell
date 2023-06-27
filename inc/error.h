#ifndef ERROR_H
# define ERROR_H

# define ERR_QUOTE "minishell: syntax error expected closing `"
# define ERR_TOKEN "minishell: syntax error near unexpected token `"
# define ERR_NOHANDLE "minishell: undefined token `"
# define ERR_CTOKEN "'\n"
# define ERR_REDIR "minishell: syntax error near unexpected token `newline'\n"

# define ERR_MISS "minishell: syntax error missing token\n"

bool	error_token(char *token, bool handle);
char	*error_quote(t_type type);
bool	error_parsing(char *msg);
void	error_exit(t_treenode **tree, t_token **l_token, char *msg);

void	free_tree(t_treenode **tree);

#endif