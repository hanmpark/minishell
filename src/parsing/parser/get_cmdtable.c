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

static int	set_mode(t_type type)
{
	if (type == AND_IF)
		return (1);
	else if (type == OR_IF)
		return (2);
	return (0);
}

// bad order bruh
static t_treenode	*get_currenttable(t_token *l_token)
{
	t_treenode	*table;
	t_cmd		*cmd;
	int			mode;

	// check_redir if parentheses
	table = NULL;
	mode = 0;
	while (l_token && l_token->type != PIPE)
	{
		cmd = get_cmd(l_token);
		if (!cmd)
			return (NULL);
		if (mode == 0)
			table = ft_treenew(cmd);
		else if (mode == 1)
			ft_treeadd_right(&table, ft_treenew(cmd));
		else if (mode == 2)
			ft_treeadd_left(&table, ft_treenew(cmd));
		l_token = next_cmd(l_token);
		if (!l_token || l_token->type == PIPE)
			break ;
		mode = set_mode(l_token->type);
		l_token = l_token->next;
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
		error_exit(NULL, &l_token, "malloc");
	i = 0;
	while (l_token && i < nb_pipeline)
	{
		cmdtable[i] = get_currenttable(l_token);
		if (!cmdtable[i])
			error_exit(cmdtable, &l_token, "malloc");
		l_token = next_pipeline(l_token);
		i++;
	}
	return (cmdtable);
}
