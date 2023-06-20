#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

/* PARSER PART (note for Hanmin):
* - treat redirections
* - '<>' is valid and it's considered to be '<'
* - create the binary tree out of the tokens only if they are valid
*/

static bool	is_redir(t_type type)
{
	return (type == DGREAT || type == DLESS || type == GREAT || type == LESS);
}

static bool	is_cmdsep(t_type type)
{
	return (type == OR_IF || type == AND_IF || type == PIPE);
}

static int	arguments(int last_type, t_cmdtable table)
{
	if (last_type == LESS && table.type != WORD && table.type != GREAT)
		return (-1);
	if (is_redir(last_type) && table.type != WORD)
		return (-1);
	else if (is_cmdsep(table.type) && last_type != WORD)
		return (-1);
	else if (table.type == SEMI || table.type == BACKSLASH)
		return (-2);
	return (table.type);
}

static bool	check_order(t_cmdtable *table)
{
	int	last_type;

	last_type = -1;
	while (table)
	{
		last_type = arguments(last_type, *table);
		if (last_type == -1)
			return (error_token(table->token, true));
		if (last_type == -2)
			return (error_token(table->token, false));
		table = table->next;
	}
	if (is_cmdsep(last_type))
		return (error_parsing(ERR_MISS));
	else if (is_redir(last_type))
		return (error_parsing(ERR_REDIR));
	return (true);
}

bool	parser(t_cmdtable *table)
{
	if (!check_order(table))
		return (false);
	return (true);
}
