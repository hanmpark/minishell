#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "error.h"

static int	count_pipeline(t_token	*l_token)
{
	int	nbr;

	nbr = 0;
	while (l_token)
	{
		if (l_token->type == PIPE)
			nbr++;
		l_token = l_token->next;
	}
	return (nbr + 1);
}

static void	add_node(t_treenode **node, t_treenode *add, t_type add_mode)
{
	if (add_mode == AND_IF)
		ft_treeadd_right(node, add);
	else if (add_mode == OR_IF)
		ft_treeadd_left(node, add);
	else
		*node = add;
}

// Get a pipeline 
static t_treenode	*get_table(t_token *l_token)
{
	t_treenode	*table;
	t_cmd		*cmd;
	t_type		add_mode;

	// check_redir if parentheses
	table = NULL;
	while (l_token && l_token->type != PIPE)
	{
		cmd = NULL;
		add_mode = l_token->type;
		if (is_cmdsep(add_mode))
			l_token = l_token->next;
		cmd = get_cmd(l_token);
		if (!cmd) // malloc problem
		{
			free_node(&table);
			return (NULL);
		}
		add_node(&table, ft_treenew(cmd), add_mode);
		l_token = next_cmd(l_token);
	}
	return (table);
}

/* Get the command table for the execution part:
* - treats redirections for commands
* - creates a tree node for each pipeline
*/
t_treenode	**get_cmdtable(t_token *l_token)
{
	t_treenode	**cmdtable;
	int			nb_pipeline;
	int			i;

	nb_pipeline = count_pipeline(l_token);
	cmdtable = ft_calloc(nb_pipeline + 1, sizeof(t_treenode *));
	if (!cmdtable)
		error_exit(NULL, &g_ms.l_token, "malloc");
	i = 0;
	while (l_token && i < nb_pipeline)
	{
		cmdtable[i] = get_table(l_token);
		if (!cmdtable[i])
			error_exit(cmdtable, &g_ms.l_token, "malloc");
		l_token = next_pipeline(l_token);
		i++;
	}
	return (cmdtable);
}
