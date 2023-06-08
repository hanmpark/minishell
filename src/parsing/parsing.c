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

/* Starting to tokenize
* It's the lexer part.
*/
void	divide(char *cmd_line, int i)
{
	
}

/* Scans the input text character by character and groups characters
* into meaningful units, such as keywords, identifiers, operators,
* and literals.
*/
bool	parsing(t_data *ms)
{
	int		i;

	if (!ms->line)
		return (false);
	i = 0;
	while (ms->line[i])
	{
		if (ms->line[i] == '$' && ft_isenv(ms->line[i + 1]))
			ms->line = treat_env(ms->line, &i);
		else
			i++;
	}
	printf("%s\n", ms->line);
	return (true);
}
