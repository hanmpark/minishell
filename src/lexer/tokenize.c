/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 07:44:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

static int	nbr_skip(char *str, t_type type)
{
	int	skip;

	if (!str)
		return (0);
	skip = 0;
	while (str[skip] && ft_isspace(str[skip]))
		skip++;
	if (type == DLESS || type == DGREAT || type == OR_IF || type == AND_IF)
		return (2);
	else if (type == UNDEFINED && is_undefined(str))
		return (is_undefined(str));
	else if ((type == UNDEFINED && *str == '&'))
		return (1);
	else if (type != WORD && !ft_isspace(*str))
		return (1);
	return (skip);
}

/*
* Skips the separator:
* - if the separator is different from spaces, tokenizes the sep.
* - else, skips spaces and go to the next token.
*/
static void	skip_sep(t_token **l_token, t_lex *lex, char *line)
{
	int	skip;

	skip = nbr_skip(line + lex->cur, lex->type);
	if (lex->type != SPACE && line[lex->cur])
		ft_tokadd_back(l_token, ft_toknew(ft_substr(line, lex->cur, skip), \
			lex->type));
	if (!skip && line[lex->cur])
		lex->cur++;
	lex->cur += skip;
	lex->last = lex->cur;
}

/*
* Creates tokens and sets their type:
* - they are stored in linked lists.
* - creates a token which stores everything between quotes without expanding
* variables.
* - returns false if the second quotation mark is not found.
*/
static bool	separate_token(t_token **l_token, t_lex *lex, char *line)
{
	char	*token;

	token = ft_substr(line, lex->last, lex->cur - lex->last);
	if (lex->type == QUOTE || lex->type == DQUOTE)
		token = tokenize_string(lex, token, line);
	if (!token)
		return (false);
	if (*token)
		ft_tokadd_back(l_token, ft_toknew(token, WORD));
	else if (!*token)
		free(token);
	skip_sep(l_token, lex, line);
	return (true);
}

/*
* Separate tokens:
* - reads each character and tokenize them by their type.
* - the line is split with the separators.
*/
bool	tokenize(t_lex *lex, char *line)
{
	lex->type = is_separator(line + lex->cur);
	if (lex->type != WORD || !line[lex->cur])
	{
		if (!separate_token(&lex->l_token, lex, line))
			return (false);
	}
	else
		lex->cur++;
	return (true);
}
