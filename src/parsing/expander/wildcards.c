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

static size_t	count_cmp(const char *pattern)
{
	size_t	cmplen;

	cmplen = 0;
	while (pattern[cmplen] && pattern[cmplen] != '*')
		cmplen++;
	return (cmplen);
}

static bool	runthrough(char *file, const char *pattern, int *i, size_t cmplen)
{
	bool	check;

	check = true;
	while (file[*i])
	{
		if (ft_strncmp(file + *i, pattern, cmplen))
			check = false;
		if (check)
			break ;
		(*i)++;
	}
	return (check);
}

static bool	check_pattern(char *file, const char *pattern)
{
	size_t	cmplen;
	bool	check;
	int		i;
	int		j;

	i = 0;
	j = 0;
	check = true;
	while (check && file[i] && pattern[j])
	{
		cmplen = count_cmp(pattern + j);
		while (pattern[j] && pattern[j] == '*')
			j++;
		if (!pattern[j])
			break ;
		check = runthrough(file, pattern + j, &i, cmplen);
		j += (int)cmplen;
	}
	return (check);
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
