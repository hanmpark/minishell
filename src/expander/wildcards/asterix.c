#include "minishell.h"
#include "expander.h"
#include <dirent.h>

static char	**init_entry(void)
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

char	**glob_or_expand(char **ar, char *arg)
{
	char	**glob_array;
	char	*exp_str;

	glob_array = asterix_globbing(arg);
	if (!glob_array || !*glob_array)
	{
		exp_str = treat_env(ft_strdup(arg), false);
		if (exp_str && *exp_str)
			ar = ft_arrayadd(ar, exp_str);
		else if (exp_str && !*exp_str)
			free(exp_str);
	}
	else
		ar = ft_arrayjoin(ar, glob_array);
	return (ar);
}

/* For each string in the array, checks if there is an asterix in the string.
* If there is at least one, perform pattern matching on filenames
* in the current directory.
*/
char	**array_iter_globbing(char **args)
{
	int		i;
	char	**res;

	if (!args)
		return (NULL);
	i = -1;
	res = ft_calloc(1, sizeof(char *));
	if (!res)
		return (NULL);
	while (args[++i])
		res = glob_or_expand(res, args[i]);
	ft_arrayfree(args);
	return (res);
}
