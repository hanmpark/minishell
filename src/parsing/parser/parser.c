#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

/* UPDATE:
* - ~ has to print the value of $HOME only if it's not a string and alone
* - instead of doing part of the expander's job in the lexer,
* do it after the parser
* - have to do the parentheses parsing
* - when doing the expander don't forget to treat the '*'
*/

// Maybe do this in recursive ? -> ((echo hi && echo hello) || (echo no && echo haha))
static bool	check_in_parentheses(t_cmdtable *table)
{
	bool	found_operator;

	found_operator = false;
	while (table && table->type == RPAR)
	{
		if (is_cmdsep(table->type))
			found_operator = true;
	}
	if (!table || !found_operator)
		return (false);
	return (true);
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
			if (!check_in_parentheses(table))
				return (false);
		}
		table = table->next;
	}
	return (true);
}

bool	parser(t_cmdtable *table)
{
	if (!check_order(table) || !check_parentheses(table))
		return (false);
	return (true);
}
