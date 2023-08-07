/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 07:43:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

static t_treenode	*addnode(t_treenode *table, t_treenode *add, t_token mode)
{
	if (!table)
		return (NULL);
	if (table->par_id == mode.par_id || !mode.par_id)
	{
		if (mode.type == 3)
			ft_treeadd_right(&table, add);
		else if (mode.type == 2)
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
static t_treenode	*get_node(t_token **l_tok, t_treenode *table, t_token mode)
{
	t_treenode	*node;

	node = ft_treenew();
	if (!node)
		return (NULL);
	node->nb_pipe = ft_countpipe(*l_tok);
	node->cmd = get_simple_cmd(l_tok, node);
	if (!node->cmd)
	{
		free_tree(node);
		free_tree(table);
		return (NULL);
	}
	if (!table)
		table = node;
	else
		table = addnode(table, node, mode);
	return (table);
}

/*
* Get the command table for the execution part:
* - handles redirections for commands.
* - creates a binary tree node for each command line.
* - expand the tokens.
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
		cmdtable = get_node(&l_tok, cmdtable, add_mode);
		if (!cmdtable)
			return (NULL);
	}
	return (cmdtable);
}
