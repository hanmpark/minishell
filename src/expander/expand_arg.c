/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:31 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 09:03:57 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static char	**join_last_element(char **array, char **join)
{
	char	*add;
	int		i;

	if (!array[0])
	{
		array = ft_arrayjoin(array, join);
		return (array);
	}
	i = 0;
	while (array[i + 1])
		i++;
	add = ft_strdup(array[i]);
	free(array[i]);
	array[i] = ft_strjoin(add, *join);
	free(add);
	if (ft_arraylen(join) > 1)
		array = ft_arrayjoin(array, join + 1);
	ft_arrayfree(join);
	return (array);
}

static char	**convert_to_array(char *arg, int *i, bool first_iter)
{
	char	*str;
	char	**array;

	if (arg[*i] == '\'' || arg[*i] == '"')
	{
		str = get_quotestr(arg, i);
		array = ft_arraynew(treat_env(ft_strdup(str), false));
	}
	else
	{
		str = word_str(arg, i);
		array = array_iter_globbing(ft_split(str, ' '));
		if (first_iter && !*array && !arg[*i])
		{
			ft_arrayfree(array);
			array = NULL;
		}
	}
	free(str);
	return (array);
}

static char	**quotes_expansion(char **cmd, char *arg, int *i)
{
	char	**expanded_array;

	expanded_array = convert_to_array(arg, i, *i == 0);
	if (!expanded_array)
	{
		ft_arrayfree(cmd);
		return (NULL);
	}
	cmd = join_last_element(cmd, expanded_array);
	return (cmd);
}

/*
* Expands the command's arguments:
* This function expands the command's arguments based on different conditions,
* such as quotes and asterisk wildcard. If the environment value is NULL
* and there are no more elements to process in the argument, it returns NULL.
*/
char	**expand_arg(char *arg)
{
	char	**cmd;
	int		i;

	cmd = ft_calloc(1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd && arg[i])
		cmd = quotes_expansion(cmd, arg, &i);
	free(arg);
	return (cmd);
}
