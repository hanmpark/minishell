/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:31 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/19 23:12:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "isft.h"

/*
* Concatenates the first string of the joining array in the last string
* of the first array. Then, simply join the remaining elements to the array.
*/
static char	**append_array(char **array, char **join)
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
		array = ft_arrayjoin(array, ft_arraydup(join + 1));
	ft_arrayfree(join);
	return (array);
}

static char	**convert_to_array(t_mnsh *mnsh, char *arg, int *i, bool begin)
{
	char	*str;
	char	**array;

	if (arg[*i] == '\'' || arg[*i] == '"')
	{
		str = extract_expand_quoted(mnsh, arg, i);
		array = ft_arraynew(ft_strdup(str));
	}
	else
	{
		str = extract_expand_unquoted(mnsh, arg, i);
		array = array_iter_globbing(mnsh, ft_split(str, &ft_isspace));
		if (begin && !*array && !arg[*i])
		{
			ft_arrayfree(array);
			array = NULL;
		}
	}
	free(str);
	return (array);
}

static char	**quotes_expansion(t_mnsh *mnsh, char **cmd, char *arg, int *i)
{
	char	**expanded_array;

	expanded_array = convert_to_array(mnsh, arg, i, *i == 0);
	if (!expanded_array)
	{
		ft_arrayfree(cmd);
		return (NULL);
	}
	cmd = append_array(cmd, expanded_array);
	return (cmd);
}

/*
* Expands the command's arguments:
* This function expands the command's arguments based on different conditions,
* such as quotes and asterisk wildcard. If the environment value is NULL
* and there are no more elements to process in the argument, it returns NULL.
*/
char	**expand_arg(t_mnsh *mnsh, char *arg)
{
	char	**cmd;
	int		i;

	cmd = ft_calloc(1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (cmd && arg[i])
		cmd = quotes_expansion(mnsh, cmd, arg, &i);
	free(arg);
	return (cmd);
}
