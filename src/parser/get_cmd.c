/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:55 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:52:57 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "exit.h"

static char	**get_args(t_token **cur, int *par_id)
{
	char	**args;
	char	**tmp;

	args = NULL;
	if (*cur && (*cur)->type == PIPE)
		*cur = (*cur)->next;
	while (*cur && !is_redir((*cur)->type) && !is_cmdsep((*cur)->type))
	{
		if (!is_par((*cur)->type))
		{
			tmp = expand_arg(ft_strdup((*cur)->token));
			if (!args)
			{
				*par_id = (*cur)->par_id;
				args = tmp;
			}
			else if (tmp)
				args = ft_arrayjoin(args, tmp);
		}
		*cur = (*cur)->next;
	}
	return (args);
}

static bool	set_cmd(t_token **l_tok, t_treenode *node, t_cmd *cmdline)
{
	if (is_redir((*l_tok)->type))
	{
		node->par_id = (*l_tok)->par_id;
		if (!treat_redir(cmdline, l_tok))
			return (false);
	}
	else
		cmdline->args = get_args(l_tok, &node->par_id);
	return (true);
}

/* Creates an array of simple commands (t_cmd *):
* - store as many simple commands there are in between the logical operators
* - for each command, treats the redirection if there is any and stores them
* in the command structure (t_cmd *)
*/
t_cmd	**get_simple_cmd(t_token **l_tok, t_treenode *node)
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
		if (!set_cmd(l_tok, node, cmd[i]))
		{
			free_cmd(cmd);
			return (NULL);
		}
		if (*l_tok && (*l_tok)->type == PIPE)
			i++;
	}
	return (cmd);
}
