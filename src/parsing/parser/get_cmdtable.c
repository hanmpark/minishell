#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "error.h"

static char	**get_cmdargs(t_token **cur, int *par_id)
{
	char	**args;

	args = NULL;
	if (*cur && (*cur)->type == PIPE)
		*cur = (*cur)->next;
	while (*cur && !is_redir((*cur)->type) && !is_cmdsep((*cur)->type))
	{
		if (!args && !is_par((*cur)->type))
		{
			args = expand_cmd(ft_strdup((*cur)->token));
			*par_id = (*cur)->par_id;
		}
		else if (!is_par((*cur)->type))
			args = ft_arrayadd(args, expand_arg(ft_strdup((*cur)->token)));
		*cur = (*cur)->next;
	}
	return (args);
}

static bool	get_cmdline(t_token **l_tok, t_treenode *node, t_cmd *cmdline)
{
	if (is_redir((*l_tok)->type))
	{
		node->par_id = (*l_tok)->par_id;
		if (!treat_redir(cmdline, l_tok))
			return (false);
	}
	else
		cmdline->args = get_cmdargs(l_tok, &node->par_id);
	return (true);
}

static t_cmd	**get_cmd(t_token **l_tok, t_treenode *node)
{
	t_cmd	**cmd;
	int		i;

	cmd = ft_calloc(node->nb_pipe + 1, sizeof(t_cmd *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (*l_tok && (*l_tok)->type != AND_IF && (*l_tok)->type != OR_IF)
	{
		if (!cmd[i])
			cmd[i] = ft_cmdnew();
		if (!get_cmdline(l_tok, node, cmd[i]))
		{
			free_cmd(cmd);
			return (NULL);
		}
		if (*l_tok && (*l_tok)->type == PIPE)
			i++;
	}
	return (cmd);
}

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
t_treenode	*get_cmdtable(t_token *l_tok)
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
			error_exit(NULL, &g_ms.l_token, "malloc");
	}
	return (cmdtable);
}
