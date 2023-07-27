#include "minishell.h"
#include "expander.h"

static int	cmp_mode(t_wc *wc, const char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i] && pattern[i] == '*')
		i++;
	while (pattern[i] && pattern[i] != '*')
		i++;
	if (!pattern[i])
		return (END);
	else if (pattern[wc->i] && pattern[wc->i] == '*')
		return (THROUGH);
	else
		return (FRONT);
}

static bool	is_match(t_wc *wc, char *file, const char *pattern)
{
	if (wc->cmpmode == FRONT)
		return (compare_front(wc, file, pattern));
	else if (wc->cmpmode == THROUGH)
		return (compare_through(wc, file, pattern));
	else if (wc->cmpmode == END)
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
	t_wc	wc;

	init_wc(&wc, pattern);
	while (pattern[wc.i])
	{
		wc.cmpmode = cmp_mode(&wc, pattern);
		while (pattern[wc.i] && pattern[wc.i] == '*')
			wc.i++;
		if (!pattern[wc.i])
			return (true);
		wc.cmplen = count_cmp(pattern + wc.i);
		if (!is_match(&wc, file, pattern))
			return (false);
		wc.i += wc.cmplen;
	}
	return (true);
}

/* Checks for each file in the current directory if it matches the pattern.
* In the end, only returns the files that matched with the pattern.
*/
char	**match_files(char **files, const char *pattern)
{
	char	**new_files;
	int		i;

	new_files = ft_calloc(1, sizeof(char *));
	if (!new_files)
		return (NULL);
	i = 0;
	while (files[i])
	{
		if (check_file(files[i], pattern))
			new_files = ft_arrayadd(new_files, ft_strdup(files[i]));
		i++;
	}
	ft_arrayfree(files);
	return (new_files);
}
