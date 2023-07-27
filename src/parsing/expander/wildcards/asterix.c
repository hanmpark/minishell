#include "minishell.h"
#include "expander.h"
#include <dirent.h>

static char	**init_entry()
{
	struct dirent	*entry;
	DIR				*dir;
	char			**files;

	files = ft_calloc(1, sizeof(char *));
	if (!files)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		files = ft_arrayadd(files, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}

void	init_wc(t_wc *wc, const char *pattern)
{
	wc->cmpmode = 0;
	wc->cmplen = 0;
	wc->i = 0;
	wc->j = 0;
	if (pattern[0] && pattern[0] == '.')
		wc->dotstart = 1;
	else
		wc->dotstart = 0;
}

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

char	**asterix_globbing(const char *pattern)
{
	char	**files;

	if (!is_wildcard(pattern))
		return (NULL);
	files = init_entry();
	if (!files)
		return (NULL);
	files = match_files(files, pattern);
	return (files);
}

/* For each string in the array, checks if there is an asterix in the string.
* If there is at least one, perform pattern matching on filenames
* in the current directory.
*/
char	**array_iter_globbing(char **args)
{
	int		i;
	char	**tmp;
	char	**res;

	i = -1;
	res = ft_calloc(1, sizeof(char *));
	if (!res)
		return (NULL);
	while (args[++i])
	{
		tmp = asterix_globbing(args[i]);
		if (!tmp || !*tmp)
			res = ft_arrayadd(res, treat_env(ft_strdup(args[i])));
		else
			res = ft_arrayjoin(res, tmp);
		if (tmp && !*tmp)
			free(tmp);
	}
	ft_arrayfree(args);
	return (res);
}
