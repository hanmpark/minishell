#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

/* UPDATE:
* - ~ has to print the value of $HOME only if it's not a string and alone
* - instead of doing part of the expander's job in the lexer,
* do it after the parser
* - when doing the expander don't forget to treat the '*'
*/

bool	parser(t_cmdtable *table)
{
	if (!check_order(table) || !check_parentheses(table))
		return (false);
	return (true);
}
