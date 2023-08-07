/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterix_globbing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:37 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 14:02:14 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static bool	is_wildcard(const char *pattern)
{
	bool	yes;
	int		i;

	i = 0;
	yes = false;
	while (pattern && pattern[i])
	{
		if (pattern[i] == '*')
			yes = true;
		if (pattern[i] == '\'' || pattern[i] == '"')
			return (false);
		i++;
	}
	return (yes);
}

static char	**asterix_globbing(const char *pattern)
{
	char	**files;

	if (!is_wildcard(pattern))
		return (NULL);
	files = init_entry_files();
	if (!files)
		return (NULL);
	files = match_files(files, pattern);
	return (files);
}

static char	**glob_or_expand(char **ar, char *arg, char **envp)
{
	char	**glob_array;
	char	*exp_str;

	glob_array = asterix_globbing(arg);
	if (!glob_array || !*glob_array)
	{
		exp_str = treat_env(ft_strdup(arg), envp, false);
		if (exp_str && *exp_str)
			ar = ft_arrayadd(ar, exp_str);
		else if (exp_str && !*exp_str)
			free(exp_str);
	}
	else
		ar = ft_arrayjoin(ar, glob_array);
	return (ar);
}

/*
* For each string in the array, checks if there is an asterix in the string.
* If there is at least one, perform pattern matching on filenames
* in the current directory.
*/
char	**array_iter_globbing(char **args, char **envp)
{
	char	**res;
	int		i;

	if (!args)
		return (NULL);
	res = ft_calloc(1, sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	while (args[++i])
		res = glob_or_expand(res, args[i], envp);
	ft_arrayfree(args);
	return (res);
}
