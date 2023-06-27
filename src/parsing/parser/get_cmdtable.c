#include "minishell.h"
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

static bool	get_currenttable(t_treenode *cur_node, t_token *l_token)
{
	t_cmd	*cmd;

	// check_redir if parentheses
	while (l_token && l_token->type != PIPE)
	{
		cmd = get_cmd(l_token);
		if (!cmd)
			return (false);
		l_token = next_cmd(l_token);
		if (l_token && l_token->type == PIPE)
			cur_node = ft_treenew(cmd);
		else if (l_token && l_token->type == AND_IF)
			ft_treeadd_right(cur_node, ft_treenew(cmd), 1);
		else if (l_token && l_token->type == OR_IF)
			ft_treeadd_left(cur_node, ft_treenew(cmd), 1);
		if (l_token && l_token->type != PIPE)
			l_token = l_token->next;
	}
	return (true);
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
		error_exit(NULL, &l_token, "malloc");
	i = 0;
	while (l_token && i < nb_pipeline)
	{
		if (!get_currenttable(cmdtable[i], l_token))
			error_exit(cmdtable, &l_token, "malloc");
		l_token = next_pipeline(l_token);
		i++;
	}
	return (cmdtable);
}
