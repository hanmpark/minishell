/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:58 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:53:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

static int	right_token(int last_type, t_token *cur)
{
	if (is_redir(last_type) && cur->type != WORD)
		return (-1);
	else if (is_cmdsep(last_type) && (!is_redir(cur->type) \
		&& cur->type != WORD && cur->type != LPAR))
		return (-1);
	else if (is_cmdsep(cur->type) && (last_type != WORD && last_type != RPAR))
		return (-1);
	else if (last_type == RPAR && (cur->type == WORD || is_redir(cur->type)))
		return (-1);
	else if (cur->type == LPAR && (last_type != -1 && !is_cmdsep(last_type) \
		&& last_type != LPAR))
		return (-2);
	else if (cur->type == UNDEFINED)
		return (-2);
	return (cur->type);
}

// Checks the order of the tokens
bool	check_order(t_token *l_token)
{
	int	last_type;

	last_type = -1;
	while (l_token)
	{
		last_type = right_token(last_type, l_token);
		if (last_type == -1)
			return (error_token(l_token->token, ERR_TOKEN, ORDER_WRONG));
		if (last_type == -2)
			return (error_token(l_token->token, ERR_NOHANDLE, NO_HANDLE));
		l_token = l_token->next;
	}
	if (is_cmdsep(last_type))
		return (error_token(NULL, ERR_MISS, NO_HANDLE));
	else if (is_redir(last_type))
		return (error_token(NULL, ERR_REDIR, ORDER_WRONG));
	return (true);
}
