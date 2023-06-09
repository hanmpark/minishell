#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "error.h"

static char	**get_cmdargs(t_token **cur)
{
	char	**args;

	args = NULL;
	while (*cur && !is_redir((*cur)->type) && !is_cmdsep((*cur)->type))
	{
		if (!args && !is_par((*cur)->type))
			args = expand_cmd(ft_strdup((*cur)->token));
		else if (!is_par((*cur)->type))
			args = ft_arrayadd(args, expand_arg(ft_strdup((*cur)->token)));
		*cur = (*cur)->next;
	}
	return (args);
}

/*
t_parfd	find_parfd(t_token *l_token)
{
	t_parfd	parfd;

	parfd.redir_in = -1;
	parfd.redir_out = -1;
	parfd.fdin = FILENO_STDIN;
	parfd.fdout = FILENO_STDOUT;
	while (l_token && l_token->par_id > 0)
		l_token = l_token->next;
	if (l_token && is_redir(l_token->type))
	{
		l_token = l_token->next;
		if (!check_filename(l_token->token))
			return (NULL);
		l_token->token = expand_arg(l_token->token);
	}
}
*/

static t_cmd	*get_cmd(t_token **l_token)
{
	t_cmd	*cmd;

	cmd = ft_cmdnew();
	if (!cmd)
		return (NULL);
	if ((*l_token)->type == LPAR)
		// do something...
		// find if there is a common fdout / fdin
	while (*l_token && !is_cmdsep((*l_token)->type))
	{
		if (is_redir((*l_token)->type))
		{
			if (!treat_redir(cmd, l_token, (*l_token)->type))
				return (cmd);
		}
		else
			cmd->args = get_cmdargs(l_token);
	}
	return (cmd);
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

static t_treenode	*get_table(t_token **l_token)
{
	t_treenode	*table;
	t_cmd		*cmd;
	t_type		add_mode;

	table = NULL;
	while (*l_token && (*l_token)->type != PIPE)
	{
		cmd = NULL;
		add_mode = (*l_token)->type;
		if (is_cmdsep(add_mode))
			*l_token = (*l_token)->next;
		cmd = get_cmd(l_token);
		if (!cmd)
		{
			free_node(&table);
			return (NULL);
		}
		add_node(&table, ft_treenew(cmd), add_mode);
	}
	return (table);
}

/* Get the command table for the execution part:
* - treats redirections for commands
* - creates a binary tree for each pipeline
* - expand the tokens
*/
t_treenode	**get_cmdtable(t_token *l_token)
{
	t_treenode		**cmdtable;
	unsigned int	nb_pipeline;
	unsigned int	i;

	nb_pipeline = ft_count_pipeline(l_token);
	cmdtable = ft_calloc(nb_pipeline + 1, sizeof(t_treenode *));
	if (!cmdtable)
		error_exit(NULL, &g_ms.l_token, "malloc");
	i = 0;
	while (l_token && i < nb_pipeline)
	{
		cmdtable[i] = get_table(&l_token);
		if (!cmdtable[i])
			error_exit(cmdtable, &g_ms.l_token, "malloc");
		if (l_token)
			l_token = l_token->next;
		i++;
	}
	return (cmdtable);
}
