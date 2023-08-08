/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treereset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:44 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

// Resets the count in every node in the tree
void	ft_treereset(t_tree *node)
{
	if (!node)
		return ;
	node->initialized = 0;
	ft_treereset(node->and_branch);
	ft_treereset(node->or_branch);
}
