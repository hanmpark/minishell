/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:54:34 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 10:25:00 by hanmpark         ###   ########.fr       */
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
	char	*tmp;
	int		i;

	tmp = ft_calloc(1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (token[i])
		tmp = extracts_join_limiter(tmp, token, &i);
	limiter = ft_strjoin(tmp, "\n");
	free(tmp);
	return (limiter);
}
