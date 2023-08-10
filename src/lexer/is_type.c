/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:11 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:45:53 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "isft.h"

/*
* In the given string, checks if the following characters match with
* one of the following undefined token that minishell does not have to handle.
*/
int	is_undefined(char *str)
{
	static t_sep	undefined[] = {{"&>>", 3}, {"<<-", 3}, {"<<<", 3}, \
		{"<>", 2}, {">|", 2}, {"&>", 2}, {">&", 2}, {"<&", 2}, {";", 1}, \
		{"\\", 1}};
	int				i;

	i = -1;
	while (++i < NBR_UDF)
		if (!ft_strncmp(str, undefined[i].cmpstr, undefined[i].bytes))
			return (undefined[i].bytes);
	return (0);
}

/*
* In the given string, checks if the following characters match with
* one of the following separators.
*/
t_type	is_separator(char *str)
{
	static t_sep	sep[] = {{"<<", 2}, {">>", 2}, {"||", 2}, {"&&", 2}, \
		{"<", 1}, {">", 1}, {"|", 1}, {"(", 1}, {")", 1}, {"\'", 1}, \
		{"\"", 1}};
	int				i;

	if (!str)
		return (-1);
	if (is_undefined(str))
		return (UNDEFINED);
	i = -1;
	while (++i < NBR_TYPES)
		if (!ft_strncmp(str, sep[i].cmpstr, sep[i].bytes))
			return (i);
	if (!ft_strncmp(str, "&", 1))
		return (UNDEFINED);
	if (ft_isspace(*str))
		return (WHITE_SPACE);
	return (WORD);
}

bool	is_redir(t_type type)
{
	return (type == DGREAT || type == DLESS || type == GREAT || type == LESS);
}

bool	is_cmdsep(t_type type)
{
	return (type == OR_IF || type == AND_IF || type == PIPE);
}

bool	is_par(t_type type)
{
	return (type == LPAR || type == RPAR);
}
