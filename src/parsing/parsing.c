#include "minishell.h"
#include <stdbool.h>

/* Starting to tokenize
* It's the lexer part.
*/
void	divide(char *cmd_line, int i)
{
	
}

static int	check_parentheses(char *line)
{
	int	i;
	int	closed;

	i = -1;
	closed = 0;
	while (line[++i])
	{
		if (line[i] == '(' || line[i] == ')')
			closed++;
	}
	return (closed % 2);
}

static int	check_quotes(char *line, bool simple)
{
	int	i;
	int closed;

	i = -1;
	closed = 0;
	while (line[++i])
	{
		if (!simple && line[i] == '"')
			closed++;
		else if (simple && line[i] == '\'')
			closed++;
	}
	return (closed % 2);
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
	if (check_parentheses(ms->line) || check_quotes(ms->line, true) || \
		check_quotes(ms->line, false))
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
