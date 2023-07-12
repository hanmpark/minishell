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
	int	i;

	wc->cmpmode = 0;
	wc->cmplen = 0;
	wc->i = 0;
	wc->j = 0;
	i = 0;
	while (pattern[i] && pattern[i] == '*')
		i++;
	if (pattern[i] && pattern[i] == '.')
		wc->dotstart = 1;
	else
		wc->dotstart = 0;
}

// Treats the asterix wildcard
char	**wildcards(const char *pattern)
{
	char	**files;

	files = init_entry();
	if (!files)
		return (NULL);
	files = match_files(files, pattern);
	return (files);
}
