/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:54:34 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/09 18:36:34 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static char	*extracts_join_limiter(char *old_limiter, char *token, int *i)
{
	char	*limiter;
	char	*tmp;
	int		start;
	int		extract_len;

	start = *i;
	if (token[*i] == '\'' || token[*i] == '"')
		start = ++(*i);
	extract_len = 0;
	while (token[*i] && token[*i] != '\'' && token[*i] != '"')
	{
		(*i)++;
		extract_len++;
	}
	tmp = ft_substr(token, start, extract_len);
	limiter = ft_strjoin(old_limiter, tmp);
	free(old_limiter);
	free(tmp);
	return (limiter);
}

/*
* Simply removes the quotation marks in the token string
* to return the limiter
*/
char	*format_limiter(char *token)
{
	char	*limiter;
	int		i;

	limiter = ft_calloc(1, sizeof(char));
	if (!limiter)
		return (NULL);
	i = 0;
	while (token[i])
		limiter = extracts_join_limiter(limiter, token, &i);
	return (limiter);
}
