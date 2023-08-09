/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:58 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/09 15:19:46 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "exit.h"

/*
* Checks file name:
* if the file name contains WHITE_SPACE / NULL after being expaneded,
* returns an error.
*/
bool	check_filename(t_mnsh *mnsh, t_tok *token)
{
	char	**expanded_token;

	expanded_token = expand_arg(mnsh, ft_strdup(token->token));
	if (!expanded_token || ft_arraylen(expanded_token) > 1)
	{
		if (expanded_token)
			ft_arrayfree(expanded_token);
		return (error_token(token->token, ERR_AMB, NO_HANDLE));
	}
	free(token->token);
	token->token = ft_strdup(*expanded_token);
	ft_arrayfree(expanded_token);
	return (true);
}

static int	right_tok(int last_type, t_tok *cur)
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
bool	check_order(t_tok *l_token)
{
	int	last_type;

	last_type = -1;
	while (l_token)
	{
		last_type = right_tok(last_type, l_token);
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

static t_tok	*check_in_parentheses(t_tok *l_token, int *par_id)
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
bool	check_parentheses(t_tok *l_token)
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
