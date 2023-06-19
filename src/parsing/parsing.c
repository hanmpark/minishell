#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>

// Prints out the tokens with their type
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

// Note for self (Kian):
// The lexer is the first step of the parsing process
// the tokens are stored in a linked list of t_cmdtable
// the tokens are separated by their type
// the tokens are then passed to the parser
// the parser will check if the tokens are in the right order

bool	parsing(t_minishell *ms)
{
	ms->table = lexer(ms->line);
	if (!ms->table)
		return (false);
	print_list(ms->table);
	if (!parser(ms->table))
		return (false);
	return (true);
}
