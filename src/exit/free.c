#include "minishell.h"

void	free_tokens(t_cmdtable **table)
{
	t_cmdtable	*current;
	t_cmdtable	*next;

	if (!*table)
		return ;
	current = *table;
	while (current)
	{
		next = current->next;
		free(current->token);
		current->token = NULL;
		free(current);
		current = next;
	}
	*table = NULL;
}
