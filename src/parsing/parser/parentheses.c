#include "minishell.h"
#include "parsing.h"
#include "error.h"

static t_cmdtable	*check_in_parentheses(t_cmdtable *table)
{
	int	found_operator;

	found_operator = 0;
	while (table)
	{
		if (table->type == LPAR)
			table = check_in_parentheses(table->next);
		else if (table->type == RPAR)
		{
			found_operator++;
			break ;
		}
		else if (table->type == OR_IF || table->type == AND_IF)
			found_operator = 1;
		if (table)
			table = table->next;
	}
	if (found_operator != 2)
		return (NULL);
	return (table);
}

/* Checks if the parentheses are:
* - closed
* - correct with the commands in it
* (they are supposed to contain at least 1 operator as the subject
* explicitly says "parentheses for priorities" and not creating subshells)
*/
bool	check_parentheses(t_cmdtable *table)
{
	while (table)
	{
		if (table->type == LPAR)
		{
			table = check_in_parentheses(table->next);
			if (!table)
				return (error_token("(", true));
		}
		else if (table->type == RPAR)
			return (error_token(")", true));
		table = table->next;
	}
	return (true);
}
