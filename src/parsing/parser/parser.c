#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>
#include <fcntl.h>

/* UPDATE (hanmin):
* - ~ has to print the value of $HOME only if it's not a string and alone
* - instead of doing part of the expander's job in the lexer,
* do it after the parser
* - when doing the expander don't forget to treat the '*'
* - don't forget about the error code !!!!
*/

t_treenode	**parser(t_token *l_token)
{
	t_treenode	**cmdtable;

	cmdtable = NULL;
	if (!check_order(l_token) || !check_parentheses(l_token))
		return (NULL);
	cmdtable = get_cmdtable(l_token);
	if (!cmdtable)
		return (NULL);
	printf("cmdtable has been created\n");
	return (cmdtable);
}
