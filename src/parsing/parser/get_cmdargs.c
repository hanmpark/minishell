#include "minishell.h"
#include "parsing.h"

static int	count_args(t_token *cur)
{
	int	len;

	len = 0;
	while (cur && !is_redir(cur->type))
	{
		len++;
		cur = cur->next;
	}
	return (len);
}

// Get the command and its arguments if it has some
char	**get_args(t_token **cur)
{
	char	**args;
	t_token	*current;
	t_token	*next;
	int		i;

	args = ft_calloc(count_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	current = *cur;
	i = 0;
	while (current && !is_redir(current->type))
	{
		next = current->next;
		args[i++] = ft_strdup(current->token);
		current = next;
	}
	*cur = current;
	return (args);
}
