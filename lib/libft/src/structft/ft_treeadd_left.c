/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeadd_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:34 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:35 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

static void	recursive_add_left(t_tree *node, t_tree *new)
{
	int	pass;

	pass = 1;
	if (!node || node->initialized)
		return ;
	if (!node->or_branch)
	{
		node->or_branch = new;
		pass = 0;
	}
	recursive_add_left(node->and_branch, new);
	if (pass)
		recursive_add_left(node->or_branch, new);
	node->initialized = 1;
}

// Adds a new node in each node's or_branch
void	ft_treeadd_left(t_tree **node, t_tree *new)
{
	if (!*node)
		*node = new;
	else
	{
		ft_treereset(*node);
		recursive_add_left(*node, new);
	}
}
