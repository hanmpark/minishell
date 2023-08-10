/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 15:50:44 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

static t_tree	*addnode(t_tree *table, t_tree *add, t_tok mode)
{
	if (!table)
		return (NULL);
	if (table->par_id == mode.par_id || !mode.par_id)
	{
		if (mode.type == AND_IF)
			ft_treeadd_right(&table, add);
		else if (mode.type == OR_IF)
			ft_treeadd_left(&table, add);
		return (table);
	}
	if (addnode(table->and_branch, add, mode) || \
		addnode(table->or_branch, add, mode))
		return (table);
	return (table);
}

/*
* Add the command table to the tree depending on:
* - the parentheses' priorities.
* - the logical operators "&&" or "||".
*/
static t_tree	*get_node(t_tok **l_tok, t_mnsh *mns, t_tree *table, t_tok mod)
{
	t_tree	*node;

	node = ft_treenew();
	if (!node)
		return (NULL);
	node->nb_pipe = ft_countpipe(*l_tok);
	node->cmd = get_simple_cmd(mns, l_tok, node);
	if (!node->cmd)
	{
		free_tree(node);
		free_tree(table);
		return (NULL);
	}
	if (!table)
		table = node;
	else
		table = addnode(table, node, mod);
	return (table);
}

/*
* Get the command table for the execution part:
* - handles redirections for commands.
* - creates a binary tree node for each command line.
* - expand the tokens.
*/
t_tree	*get_table(t_tok *l_tok, t_mnsh *mnsh)
{
	t_tree	*cmdtable;
	t_tok	add_mode;

	cmdtable = NULL;
	while (l_tok)
	{
		add_mode = *l_tok;
		if (l_tok->type == AND_IF || l_tok->type == OR_IF)
			l_tok = l_tok->next;
		cmdtable = get_node(&l_tok, mnsh, cmdtable, add_mode);
		if (!cmdtable)
			return (NULL);
	}
	return (cmdtable);
}
