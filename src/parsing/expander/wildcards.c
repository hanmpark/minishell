#include "minishell.h"
#include "expander.h"
#include "parsing.h"
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

static int	count_cmp(const char *pattern)
{
	int	len;

	len = 0;
	while (pattern[len] && pattern[len] != '*')
		len++;
	return (len);
}

static int	check_frontend(t_wc *wc, const char *pattern)
{
	int	tmp;

	tmp = wc->i;
	while (pattern[tmp] && pattern[tmp] != '*')
		tmp++;
	if (!pattern[tmp])
	{
		wc->i = tmp;
		return (END);
	}
	else if (pattern[wc->i] && pattern[wc->i] == '*')
	{
		while (pattern[wc->i] && pattern[wc->i] == '*')
			wc->i++;
		return (FRONT);
	}
	else
		return (NORM);
}

static bool	cmp_pattern(t_wc *wc, char *file, const char *pattern)
{
	if (wc->frontend == NORM)
	{
		if (!ft_strncmp(file + wc->j, pattern + wc->i, wc->cmplen))
		{
			wc->j += wc->cmplen;
			return (true);
		}
	}
	else if (wc->frontend == FRONT)
	{
		while (file[wc->j])
		{
			if (!ft_strncmp(file + wc->j, pattern + wc->i, wc->cmplen))
			{
				wc->j += wc->cmplen;
				return (true);
			}
			wc->j++;
		}
	}
	else if (wc->frontend == END)
	{
		while (file[wc->j] && wc->j < (int)ft_strlen(file) - wc->cmplen)
			wc->j++;
		if (!ft_strncmp(file + wc->j, pattern + wc->i, wc->cmplen))
		{
			wc->j += wc->cmplen;
			return (true);
		}
	}
	return (false);
}

static void	init_wc(t_wc *wc)
{
	wc->cmplen = 0;
	wc->frontend = 0;
	wc->i = 0;
	wc->j = 0;
}

static bool	check_pattern(char *file, const char *pattern)
{
	t_wc	wc;

	init_wc(&wc);
	while (pattern[wc.i])
	{
		wc.frontend = check_frontend(&wc, pattern);
		if (!pattern[wc.i])
			return (true);
		wc.cmplen = count_cmp(pattern + wc.i);
		if (!cmp_pattern(&wc, file, pattern))
			return (false);
		wc.i += wc.cmplen;
	}
	return (true);
}

static char	**find_pattern(char **files, const char *pattern)
{
	char	**new_files;
	int		i;

	new_files = ft_calloc(1, sizeof(char *));
	if (!new_files)
		return (NULL);
	i = 0;
	while (files[i])
	{
		if (check_pattern(files[i], pattern))
			new_files = ft_arrayadd(new_files, ft_strdup(files[i]));
		i++;
	}
	ft_arrayfree(files);
	return (new_files);
}

// Treats the asterix wildcard
char	**wildcards(const char *pattern)
{
	char	**files;

	files = init_entry();
	if (!files)
		return (NULL);
	files = find_pattern(files, pattern);
	return (files);
}

// test
int	main(int argc, char *argv[]) {
	char	**files;

	if (argc < 2)
		return 1;
	for (int i = 1; argv[i] != NULL; i++) {
		files = wildcards(argv[i]);
	}
	for (int i = 0; files[i]; i++) {
		printf("%s\n", files[i]);
	}
	ft_arrayfree(files);
	return 0;
}
