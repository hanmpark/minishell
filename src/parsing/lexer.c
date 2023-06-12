#include "minishell.h"
#include <stdbool.h>

static bool	is_dsym(char *symbol, char c)
{
	return (*symbol == c && *symbol + 1 == c);
}

static bool	is_sym(char symbol)
{
	return (symbol == '|' || symbol == '<' || symbol == '>');
}

static bool	is_sep(char *symbol)
{
	return (is_dsym(symbol, '&') || is_dsym(symbol, '|') || \
		is_dsym(symbol, '<') || is_dsym(symbol, '>') || is_sym(*symbol) || \
		ft_isspace(*symbol));
}

int	check_type(char *str, int *i)
{
	if (str[*i] == '|' && str[*i + 1] == '|')
		return (OR_IF);
	else if (str[*i] == '|')
		return (PIPE);
	else if (str[*i] == '&' && str[*i + 1] == '&')
		return (AND_IF);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		return (DLESS);
	else if (str[*i] == '<')
		return (LESS);
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return (DGREAT);
	else if (str[*i] == '>')
		return (GREAT);
	else if (str[*i] == '(')
		return (LPAR);
	else if (str[*i] == ')')
		return (RPAR);
	else
		return (WORD);
}

/* Starting to tokenize
* It's the lexer part
*/
t_cmdtable	*lexer(char *line)
{
	t_cmdtable	*table;
	char		*token;
	t_type		type;
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		// quotes
		if (is_sep(line + i))
		{
			ft_lstadd_back(&table, ft_lstnew(ft_strndup(line + j, i - j), \
				WORD));
			type = check_type(line, &i);
			j = i;
		}

	}
	return (table);
}
