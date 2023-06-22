#include "minishell.h"
#include "parsing.h"
#include "error.h"

static int	right_token(int last_type, t_cmdtable cur)
{
	if (is_redir(last_type) && cur.type != WORD)
		return (-1);
	else if (is_cmdsep(cur.type) && last_type != WORD)
		return (-1);
	else if (cur.type == UNDEFINED)
		return (-2);
	return (cur.type);
}

bool	check_order(t_cmdtable *table)
{
	int	last_type;

	last_type = -1;
	while (table)
	{
		last_type = right_token(last_type, *table);
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
