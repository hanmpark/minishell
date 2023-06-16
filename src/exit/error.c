#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

bool	init_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (false);
}

bool	error_quote(t_type type)
{
	if (type == DQUOTE)
		ft_putstr_fd(ERR_DQUOTE, 2);
	else
		ft_putstr_fd(ERR_QUOTE, 2);
	return (false);
}
