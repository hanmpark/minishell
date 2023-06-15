#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>

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
	ms->table = lexer(ms->line);
	if (!ms->table)
		return (false);
	print_list(ms->table);
	return (true);
}
