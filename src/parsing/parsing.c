#include "minishell.h"
#include <stdbool.h>

// static bool	check_quote(char *cmd_line)
// {
// 	int		i;
// 	t_quote	quote;
// 	t_quote	dquote;

// 	quote = NONE;
// 	dquote = NONE;
// 	i = 0;
// 	while (cmd_line[i])
// 	{
// 		if (cmd_line[i] == '\'')
// 			quote++;
// 		else if (cmd_line[i] == '"')
// 			dquote++;
// 		if (quote == CLOSED)
// 			quote = NONE;
// 		if (dquote == CLOSED)
// 			dquote = NONE;
// 		i++;
// 	}
// 	if (quote != NONE || dquote != NONE)
// 		return (false);
// 	return (true);
// }

/* Scans the input text character by character and groups characters
* into meaningful units, such as keywords, identifiers, operators,
* and literals.
*/
bool	parsing(char *cmd_line)
{
	int		i;
	char	*line;

	if (!cmd_line)
		return (false);
	line = ft_strdup(cmd_line);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ft_isenv(line[i + 1]))
			line = treat_env(line, &i);
		else
			i++;
	}
	printf("%s\n", line);
	return (true);
}
