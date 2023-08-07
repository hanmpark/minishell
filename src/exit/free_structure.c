/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:40 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 13:53:04 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Frees the tokens that was used in the parsing part
void	free_tokens(t_tok **l_token)
{
	t_tok	*current;
	t_tok	*next;

	if (!*l_token)
		return ;
	current = *l_token;
	while (current)
	{
		next = current->next;
		free(current->token);
		current->token = NULL;
		free(current);
		current = next;
	}
	*l_token = NULL;
}

// Clears the t_cmd structure by closing file descriptors and freeing arrays
void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i]->fdin != STDIN_FILENO && cmd[i]->fdin != -1)
			close(cmd[i]->fdin);
		if (cmd[i]->fdout != STDOUT_FILENO && cmd[i]->fdout != -1)
			close(cmd[i]->fdout);
		ft_arrayfree(cmd[i]->args);
		free(cmd[i]);
		i++;
	}
	if (cmd)
		free(cmd);
}

static void	free_node(t_tree **node)
{
	if (!(*node))
		return ;
	free_node(&(*node)->and_branch);
	free_node(&(*node)->or_branch);
	if ((*node)->rec_cycles == 1)
	{
		free_cmd((*node)->cmd);
		free(*node);
		*node = NULL;
	}
	else
		(*node)->rec_cycles--;
}

/*
* Frees the entire AST:
* - each existing node in the AST is cleared.
* - every structure that the node contains is cleared.
*/
void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	ft_treeset_cycles(tree);
	free_node(&tree);
}
