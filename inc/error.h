#ifndef ERROR_H
# define ERROR_H

# define ERR_QUOTE "minishell: syntax error expected closing `"
# define ERR_TOKEN "minishell: syntax error near unexpected token `"
# define ERR_NOHANDLE "minishell: undefined token `"
# define ERR_CTOKEN "'\n"

# define ERR_MISS "minishell: syntax error missing token\n"

bool	error_token(char *token, bool handle);
bool	error_quote(t_type type);
bool	error_parsing(char *msg);

#endif