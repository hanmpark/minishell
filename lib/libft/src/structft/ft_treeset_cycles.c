/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeset_cycles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:46 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:48 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

// Counts how many times it has to pass in a node to run through the whole tree
void	ft_treeset_cycles(t_tree *node)
{
	if (!node)
		return ;
	ft_treeset_cycles(node->and_branch);
	ft_treeset_cycles(node->or_branch);
	node->rec_cycles++;
}
