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

bool	parser(t_token *l_token)
{
	if (!check_order(l_token) || !check_parentheses(l_token))
		return (false);
	return (true);
}
