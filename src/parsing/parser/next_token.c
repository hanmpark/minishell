#include "minishell.h"
#include "parsing.h"
#include "error.h"

t_token	*next_cmd(t_token *l_token)
{
	while (l_token && !is_cmdsep(l_token->type))
		l_token = l_token->next;
	return (l_token);
}

t_token	*next_token(t_token *l_token)
{
	while (l_token && !is_redir(l_token->type) && !is_cmdsep(l_token->type))
		l_token = l_token->next;
	return (l_token);
}

t_token	*next_pipeline(t_token *l_token)
{
	while (l_token && l_token->type != PIPE)
		l_token = l_token->next;
	if (l_token)
		return (l_token->next);
	return (l_token);
}
