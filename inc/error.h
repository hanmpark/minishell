#ifndef ERROR_H
# define ERROR_H

# define ERR_DQUOTE "minishell: syntax error expected closing quote `\"'\n"
# define ERR_QUOTE "minishell: syntax error expected closing quote `\''\n"

bool	init_error(char *msg);
bool	error_quote(t_type type);

#endif