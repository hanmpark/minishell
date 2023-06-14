#include "minishell.h"
#include <stdbool.h>

t_type	is_separator(char *str)
{
	static t_sep	sep[] = {{"<<", 2}, {">>", 2}, {"||", 2}, {"&&", 2}, \
		{"<", 1}, {">", 1}, {"|", 1}, {"(", 1}, {")", 1}, {"\'", 1}, \
		{"\"", 1}};
	int	i;

	i = -1;
	while (++i < NBR_TYPES)
		if (!ft_strncmp(str, sep[i].line, sep[i].cmp))
			return (i);
	if (ft_isspace(*str))
		return (SPACE);
	else
		return (WORD);
}

int	skip_sep(char *str)
{
	int	skip;

	skip = 0;
	if (!str)
		return (0);
	while (str[skip] && ft_isspace(str[skip]))
		skip++;
	if (is_separator(str) == DLESS || is_separator(str) == DGREAT || \
		is_separator(str) == OR_IF || is_separator(str) == AND_IF)
		return (2);
	else if (is_separator(str) != WORD)
		return (1);
	else
		return (skip);
}

int	separate_token(t_cmdtable **table, char *line, int end)
{
	t_type		type;
	char		*token;
	static int	j = 0;

	type = is_separator(line + end);
	if (type != WORD || !line[end])
	{
		token = ft_strndup(line + j, end - j);
		if (token)
			ft_lstadd_back(table, ft_lstnew(token, WORD));
		j = skip_sep(line + end);
		if (type != SPACE && line[end])
			ft_lstadd_back(table, ft_lstnew(ft_strndup(line + end, j), type));
		end += j;
		if (line[end])
			j = end;
		return (end);
	}
	return (end + 1);
}

int	string_token(t_cmdtable **table, char *line, int i)
{
	t_type	type;
	char	*token;
	char	next;
	int		start;

	type = is_separator(line + i);
	next = line[i];
	i++;
	start = i;
	while (line[i] && line[i] != next)
		i++;
	if (!line[i])
		return (-1);
	token = ft_strndup(line + start, i - start);
	if (token)
		ft_lstadd_back(table, ft_lstnew(token, type));
	return (i + 1);
}

/* Starting to tokenize
* It's the lexer part
*/
t_cmdtable	*lexer(char *line)
{
	t_cmdtable	*table;
	int			i;

	i = 0;
	table = NULL;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			i = string_token(&table, line, i);
		else
			i = separate_token(&table, line, i);
		if (i == -1)
		{
			free_tokens(&table);
			return (NULL);
		}
	}
	separate_token(&table, line, i);
	return (table);
}
