#include "minishell.h"
#include "parsing.h"
#include "exit.h"
#include <stdbool.h>

bool	error_token(char *token, bool handle)
{
	if (handle)
		ft_putstr_fd(ERR_TOKEN, 2);
	else
		ft_putstr_fd(ERR_NOHANDLE, 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(ERR_CTOKEN, 2);
	g_ms.exit_status = 258;
	return (false);
}

char	*error_quote(t_type type)
{
	ft_putstr_fd(ERR_TOKEN, 2);
	if (type == QUOTE)
		ft_putstr_fd("'", 2);
	else
		ft_putstr_fd("\"", 2);
	ft_putstr_fd(ERR_CTOKEN, 2);
	g_ms.exit_status = 258;
	return (NULL);
}

bool	error_bool(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (false);
}

void	error_exit(t_treenode *tree, t_token **l_token, char *msg, int st)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (st == BIN_NOT_FOUND)
		ft_putstr_fd(": command not found\n", 2);
	free_tree(tree);
	free_tokens(l_token);
	close(g_ms.stdin_fileno);
	close(g_ms.stdout_fileno);
	set_termios(false);
	exit(st);
}

bool	error_expand(char *error_token, char *msg, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (msg)
	{
		ft_putstr_fd(error_token, 2);
		ft_putstr_fd(msg, 2);
	}
	else
		perror(error_token);
	g_ms.exit_status = error_code;
	return (false);
}
