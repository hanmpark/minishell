#include "minishell.h"
#include "expander.h"
#include "expander.h"
#include "parsing.h"

static bool	is_wildcard(char *pattern)
{
	int	i;

	i = 0;
	while (pattern && pattern[i])
	{
		if (pattern[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

static char	**treat_wildcards(char **args)
{
	int		i;
	char	**tmp;
	char	**res;

	i = -1;
	res = ft_calloc(1, sizeof(char *));
	if (!res)
		return (NULL);
	while (args[++i])
	{
		if (is_wildcard(args[i]))
		{
			tmp = wildcards(args[i]);
			res = ft_arrayjoin(res, tmp);
		}
		else
			res = ft_arrayadd(res, ft_strdup(args[i]));
	}
	ft_arrayfree(args);
	return (res);
}

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
	args = treat_wildcards(args);
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

t_cmd	**get_cmd(t_token **l_tok, t_treenode *node)
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
