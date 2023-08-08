/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:07 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:08 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

// Adds a new node at the end of a linked list.
void	ft_tokadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*node;

	if (!*lst)
		*lst = new;
	else
	{
		node = ft_toklast(*lst);
		node->next = new;
	}
}
