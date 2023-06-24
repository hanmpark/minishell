#include "minishell.h"
#include "parsing.h"

// Note for self (Kian):
/*
examples:
$ echo hello world
>hello world
$ echo -n hello world
>hello world%
$ echo -nnnnnnnn hello there
>hello there%
$ echo -nnnnn -nnnnnnt hello world
>-nnnnnnt hello world%
$ echo bonjour -n hello world
>bonjour -n hello world%
*/

static bool	n_identifier(char *token)
{
	int		i;
	bool	n_option;

	i = 0;
	n_option = false;
	if (token[0] == '-')
		i++;
	while (token[i])
	{
		if (token[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	put_var(char *token)
{
	// need to handle environment variables
}

void	ft_echo(t_token *l_token)
{
	t_token	*tmp;
	bool	n_option;

	n_option = false;
	tmp = l_token->next;
	if (tmp && n_identifier(tmp->token))
	{
		n_option = true;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		// if (!ft_strncmp(tmp->token, "~", 2))
		// 	put_tild(tmp->token);
		// else
			put_var(tmp->token);
		if (tmp->next)
			ft_putchar_fd(' ', 1);
		tmp = tmp->next;
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
}
