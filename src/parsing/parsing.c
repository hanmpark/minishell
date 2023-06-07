#include "minishell.h"
#include <stdbool.h>

static bool	check_quote(char *cmd_line)
{
	int		i;
	t_quote	quote;
	t_quote	dquote;

	quote = NONE;
	dquote = NONE;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'')
			quote++;
		else if (cmd_line[i] == '"')
			dquote++;
		if (quote == CLOSED)
			quote = NONE;
		if (dquote == CLOSED)
			dquote = NONE;
		i++;
	}
	if (quote != NONE || dquote != NONE)
		return (false);
	return (true);
}

/**/
char	*ft_replace(char *line, char *replace, int start)
{
	char	*tmp;
	char	*str;

	str = ft_substr(line, 0, start);
	if (!str)
		return (NULL);
	tmp = ft_strjoin(str, replace);
	while (line[start] && !ft_isspace(line[start]))
		start++;
	free(str);
	str = ft_strjoin(tmp, line + start);
	free(tmp);
	return (str);
}

/* Scans the input text character by character and groups characters
* into meaningful units, such as keywords, identifiers, operators,
* and literals.
*/
bool	parsing(char *cmd_line)
{
	int	i;
	char	*line;

	if (!cmd_line)
		return (false);
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '')
		i++;
	}
}
