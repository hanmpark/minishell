#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

/* PARSER PART (note for Hanmin):
* - treat redirections
* - '<>' is valid and it's considered to be '<'
* - create the binary tree out of the tokens only if they are valid
*/


static bool	check_order(t_cmdtable *table)
{
	bool		found_sep;

	found_sep = false;
	while (table)
	{
		if (found_sep && table->type != WORD)
			return (error_token(table->token, true));
		else if (found_sep)
			found_sep = false;
		else if (table->type == SEMI || table->type == BACKSLASH) // We don't have to handle them
			return (error_token(table->token, false));
		else if (table->type != WORD)
			found_sep = true;
		table = table->next;
	}
	if (found_sep)
		return (error_parsing(ERR_MISS));
	return (true);
}

bool	parser(t_cmdtable *table)
{
	if (!check_order(table))
		return (false);
	return (true);
}
