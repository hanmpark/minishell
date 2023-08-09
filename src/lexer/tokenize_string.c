/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:07 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/09 15:19:38 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

static bool	find_second_mark(t_lex *lex, char *line, char quote)
{
	lex->cur++;
	while (line[lex->cur] && line[lex->cur] != quote)
		lex->cur++;
	if (!line[lex->cur])
		return (false);
	lex->cur++;
	return (true);
}

static bool	move_to_end(t_lex *lex, char *line)
{
	while (line[lex->cur] && \
		(lex->type == DQUOTE || lex->type == QUOTE || lex->type == WORD))
	{
		if (lex->type == DQUOTE || lex->type == QUOTE)
		{
			if (!find_second_mark(lex, line, line[lex->cur]))
			{
				if (lex->type == DQUOTE)
					return (error_token("\"", ERR_TOKEN, NO_HANDLE));
				else if (lex->type == QUOTE)
					return (error_token("'", ERR_TOKEN, NO_HANDLE));
			}
		}
		else
			lex->cur++;
		lex->type = is_separator(line + lex->cur);
	}
	return (true);
}

static char	*get_string(t_lex *lex, t_mnsh *mnsh, char *token)
{
	char	*add_str;
	char	*final_str;

	if (!move_to_end(lex, mnsh->line))
	{
		free(token);
		return (NULL);
	}
	add_str = ft_substr(mnsh->line, lex->last, lex->cur - lex->last);
	final_str = ft_strjoin(token, add_str);
	free(add_str);
	free(token);
	return (final_str);
}

/*
* When a quote is found in the line, as long as it is not closed or separated
* by another separator, takes the whole string in the same token.
*/
char	*tokenize_string(t_lex *lex, t_mnsh *mnsh, char *token)
{
	lex->last = lex->cur;
	token = get_string(lex, mnsh, token);
	if (!token)
		return (NULL);
	return (token);
}
