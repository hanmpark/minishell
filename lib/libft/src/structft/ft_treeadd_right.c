/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeadd_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:36 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:38 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

static void	recursive_add_right(t_tree *node, t_tree *new)
{
	int	pass;

	pass = 1;
	if (!node || node->initialized)
		return ;
	if (!node->and_branch)
	{
		node->and_branch = new;
		pass = 0;
	}
	recursive_add_right(node->or_branch, new);
	if (pass)
		recursive_add_right(node->and_branch, new);
	node->initialized = 1;
}

// Adds a new node in each node's and_branch
void	ft_treeadd_right(t_tree **node, t_tree *new)
{
	if (!*node)
		*node = new;
	else
	{
		ft_treereset(*node);
		recursive_add_right(*node, new);
	}
}
