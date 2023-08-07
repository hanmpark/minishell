/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthese.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:48 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 07:42:47 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

static t_token	*check_in_parentheses(t_token *l_token, int *par_id)
{
	int	found_operator;

	found_operator = 0;
	while (l_token)
	{
		l_token->par_id = *par_id;
		if (l_token->type == LPAR)
		{
			l_token->par_id = ++(*par_id);
			l_token = check_in_parentheses(l_token->next, par_id);
		}
		else if (l_token->type == RPAR)
		{
			found_operator++;
			break ;
		}
		else if (l_token->type == OR_IF || l_token->type == AND_IF)
			found_operator = 1;
		if (l_token)
			l_token = l_token->next;
	}
	if (found_operator != 2)
		return (NULL);
	return (l_token);
}

/*
* Checks parentheses:
* - returns false if the parentheses are not closed.
* - returns true if parentheses are closed and have at least
* one logical operators, either '&&' or '||'.
*/
bool	check_parentheses(t_token *l_token)
{
	int	par_id;

	par_id = 0;
	while (l_token)
	{
		if (l_token->type == LPAR)
		{
			l_token->par_id = ++par_id;
			l_token = check_in_parentheses(l_token->next, &par_id);
			if (!l_token)
				return (error_token("(", ERR_TOKEN, NO_HANDLE));
		}
		else if (l_token->type == RPAR)
			return (error_token(")", ERR_TOKEN, NO_HANDLE));
		l_token = l_token->next;
	}
	return (true);
}
