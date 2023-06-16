#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

bool	error_token(char *token, bool handle)
{
	if (handle)
		ft_putstr_fd(ERR_TOKEN, 2);
	else
		ft_putstr_fd(ERR_NOHANDLE, 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(ERR_CTOKEN, 2);
	return (false);
}

bool	error_quote(t_type type)
{
	ft_putstr_fd(ERR_TOKEN, 2);
	if (type == QUOTE)
		ft_putstr_fd("'", 2);
	else
		ft_putstr_fd("\"", 2);
	ft_putstr_fd(ERR_CTOKEN, 2);
	return (false);
}

bool	error_parsing(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (false);
}
