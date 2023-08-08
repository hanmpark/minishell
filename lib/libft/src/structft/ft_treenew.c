/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:39 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

#include <stdlib.h>

// Creates a new node for the tree
t_tree	*ft_treenew(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->rec_cycles = 0;
	node->initialized = 0;
	node->nb_pipe = 0;
	node->cmd = NULL;
	node->or_branch = NULL;
	node->and_branch = NULL;
	return (node);
}
