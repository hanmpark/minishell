#include "minishell.h"
#include "parsing.h"
#include "error.h"

static t_treenode	*node_to_tree(t_token **l_tok, t_treenode *table, t_token mode)
{
	t_treenode	*node;

	node = ft_treenew();
	if (!node)
		return (NULL);
	node->nb_pipe = ft_countpipe(*l_tok);
	node->cmd = get_cmd(l_tok, node);
	if (!node->cmd)
	{
		free_tree(node);
		free_tree(table);
		return (NULL);
	}
	if (!table)
		table = node;
	else
		table = ft_addnode(table, node, mode);
	return (table);
}

/* Get the command table for the execution part:
* - treats redirections for commands
* - creates a binary tree for each pipeline
* - expand the tokens
*/
t_treenode	*get_table(t_token *l_tok)
{
	t_treenode	*cmdtable;
	t_token		add_mode;

	cmdtable = NULL;
	while (l_tok)
	{
		add_mode = *l_tok;
		if (l_tok->type == AND_IF || l_tok->type == OR_IF)
			l_tok = l_tok->next;
		cmdtable = node_to_tree(&l_tok, cmdtable, add_mode);
		if (!cmdtable)
			return (NULL);
	}
	return (cmdtable);
}
