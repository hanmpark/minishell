/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:28 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 09:27:03 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

/*
* Extracts and expands a quoted part of a token string:
* - extracts the first part of the token string until it reaches
* its closing quotation mark.
* - if the extracted part is from simple quotes, does not expand it.
* - else if the extracted part is from double quotes, expands it.
*/
char	*extract_expand_quoted(char *arg, int *i)
{
	char	quote_type;
	int		start;
	char	*str;

	quote_type = arg[*i];
	start = ++(*i);
	while (arg[*i] && arg[*i] != quote_type)
		(*i)++;
	str = ft_substr(arg, start, *i - start);
	if (quote_type == '"')
		str = treat_env(str, false);
	++(*i);
	return (str);
}

/*
* Extracts and expands an unquoted part of a token string:
* - extracts the first part of the token string until it reaches
* NULL or a quotation mark.
* - expands the extracted part.
*/
char	*extract_expand_unquoted(char *arg, int *i)
{
	char	*str;
	int		start;
	bool	prevent_eval;

	prevent_eval = false;
	start = *i;
	while (arg[*i] && (arg[*i] != '\'' && arg[*i] != '"'))
	{
		(*i)++;
		if (arg[*i] == '\'' || arg[*i] == '"')
			prevent_eval = true;
	}
	str = treat_env(ft_substr(arg, start, *i - start), prevent_eval);
	return (str);
}
