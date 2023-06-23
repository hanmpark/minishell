#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>

// Prints out the tokens with their type (ONLY FOR DEBUG PURPOSE)
static void	print_list(t_cmdtable *table)
{
	int	count;

	count = 0;
	while (table)
	{
		printf("[%d] token = [%s] type = %d\n", count, table->token, table->type);
		table = table->next;
		count++;
	}
	printf("\n");
}

// Note for self (Kian):
// The lexer is the first step of the parsing process
// the tokens are stored in a linked list of t_cmdtable
// the tokens are separated by their type
// the tokens are then passed to the parser
// the parser will check if the tokens are in the right order

/* Parses the given line:
* - creates tokens
* - checks the order of the token (parentheses, redirection, etc.)
* - deals with redirections
* - creates the binary tree (or not if it is a simple command line)
*/
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
