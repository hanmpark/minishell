#include "minishell.h"
#include <stdbool.h>

// static int	check_parentheses(char *line)
// {
// 	int	i;
// 	int	closed;

// 	i = -1;
// 	closed = 0;
// 	while (line[++i])
// 	{
// 		if (line[i] == '(' || line[i] == ')')
// 			closed++;
// 	}
// 	return (closed % 2);
// }

// static int	check_quotes(char *line, bool simple)
// {
// 	int	i;
// 	int closed;

// 	i = -1;
// 	closed = 0;
// 	while (line[++i])
// 	{
// 		if (!simple && line[i] == '"')
// 			closed++;
// 		else if (simple && line[i] == '\'')
// 			closed++;
// 	}
// 	return (closed % 2);
// }

static void	print_list(t_cmdtable *table)
{
	int	count;

	count = 0;
	while (table)
	{
		printf("[%d] token = \"%s\" type = %d\n", count, table->token, table->type);
		table = table->next;
		count++;
	}
	printf("\n");
}

/* Scans the input text character by character and groups characters
* into meaningful units, such as keywords, identifiers, operators,
* and literals.
*/
bool	parsing(t_minishell *ms)
{
	// int		i;

	if (!ms->line)
		return (false);
	// if (!check_parentheses(ms->line) || !check_quotes(ms->line, true) || \
	// 	!check_quotes(ms->line, false))
		// return (false);
	ms->table = lexer(ms->line);
	if (!ms->table)
		return (false);
	// i = 0;
	// while (ms->line[i])
	// {
	// 	if (ms->line[i] == '$' && ft_isenv(ms->line[i + 1]))
	// 		ms->line = treat_env(ms->line, &i);
	// 	else
	// 		i++;
	// }
	print_list(ms->table);
	// printf("%s\n", ms->line);
	return (true);
}
