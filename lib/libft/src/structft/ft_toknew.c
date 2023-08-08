/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toknew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:40:24 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:40:33 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structft.h"

#include <stdlib.h>

// Creates a new linked list node.
t_tok	*ft_toknew(char *token, int type)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	tok->token = token;
	tok->type = type;
	tok->next = NULL;
	tok->par_id = 0;
	return (tok);
}
