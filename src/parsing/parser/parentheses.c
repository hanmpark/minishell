#include "minishell.h"
#include "parsing.h"
#include "error.h"

static t_token	*check_in_parentheses(t_token *l_token)
{
	while (l_token)
	{
		if (l_token->type == LPAR)
			l_token = check_in_parentheses(l_token->next);
		else if (l_token->type == RPAR)
			return (l_token);
		if (l_token)
			l_token = l_token->next;
	}
	return (NULL);
}

/* Checks if the parentheses are:
* - closed
* NOTE: the subject of the minishell explicitly says to manage parentheses
* for priorities only. Thus, commands found between parentheses will not
* create a subshell.
*/
bool	check_parentheses(t_token *l_token)
{
	while (l_token)
	{
		if (l_token->type == LPAR)
		{
			l_token = check_in_parentheses(l_token->next);
			if (!l_token)
				return (error_token("(", true));
		}
		else if (l_token->type == RPAR)
			return (error_token(")", true));
		l_token = l_token->next;
	}
	return (true);
}
