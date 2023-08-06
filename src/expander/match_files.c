/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:18 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/06 19:36:56 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static int	cmp_mode(t_ag *wc, const char *pattern)
{
	bool	is_start;
	int		i;

	is_start = false;
	if (wc->i == 0)
		is_start = true;
	if (is_start && pattern[wc->i] != '*')
		return (GLOB_FRONT);
	while (pattern[wc->i] && pattern[wc->i] == '*')
		wc->i++;
	i = wc->i;
	while (pattern[i] && pattern[i] != '*')
		i++;
	if (!pattern[i])
		return (GLOB_END);
	return (GLOB_MID);
}

static bool	is_match(t_ag *wc, char *file, const char *pattern)
{
	if (wc->cmpmode == GLOB_FRONT)
		return (compare_front(wc, file, pattern));
	else if (wc->cmpmode == GLOB_MID)
		return (compare_mid(wc, file, pattern));
	else if (wc->cmpmode == GLOB_END)
		return (compare_end(wc, file, pattern));
	return (false);
}

static int	count_cmp(const char *pattern)
{
	int	len;

	len = 0;
	while (pattern[len] && pattern[len] != '*')
		len++;
	return (len);
}

static bool	check_file(char *file, const char *pattern)
{
	t_ag	wc;

	wc.cmpmode = 0;
	wc.cmplen = 0;
	wc.i = 0;
	wc.j = 0;
	if (pattern[0] && pattern[0] == '.')
		wc.dotstart = 1;
	else
		wc.dotstart = 0;
	while (pattern[wc.i])
	{
		wc.cmpmode = cmp_mode(&wc, pattern);
		wc.cmplen = count_cmp(pattern + wc.i);
		if (!is_match(&wc, file, pattern))
			return (false);
		wc.i += wc.cmplen;
	}
	return (true);
}

/*
* Checks for each file in the current directory if it matches the pattern.
* In the end, only returns the files that matched with the pattern.
*/
char	**match_files(char **files, const char *pattern)
{
	char	**new_files;
	int		i;

	new_files = ft_calloc(1, sizeof(char *));
	if (!new_files)
		return (NULL);
	i = -1;
	while (files[++i])
		if (check_file(files[i], pattern))
			new_files = ft_arrayadd(new_files, ft_strdup(files[i]));
	if (!*new_files)
	{
		free(new_files);
		new_files = NULL;
	}
	ft_arrayfree(files);
	return (new_files);
}
