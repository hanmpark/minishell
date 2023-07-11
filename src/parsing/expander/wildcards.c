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

static int	count_cmp(char *pattern)
{
	int	len;

	len = 0;
	while (pattern[len] && pattern[len] != '*')
		len++;
	return (len);
}

static bool	runthrough(char *file, const char *pattern, int *i, int frontend)
{
	int	cmplen;

	cmplen = count_cmp(pattern);
	if (!frontend)
		if (!ft_strncmp(file + *i, pattern, cmplen))
			return (true);
	if (frontend == 1)
	{
		while (file[*i])
		{
			if (!ft_strncmp(file + *i, pattern, cmplen))
				return (true);
			*i++;
		}
	}
	return (false);
}

static bool	check_pattern(char *file, const char *pattern)
{
	int	frontend;
	int	i;
	int	j;

	frontend = 0;
	i = 0;
	j = 0;
	while (pattern[j])
	{
		if (pattern[j] == '*')
		{
			frontend = 1;
			j++;
		}
		else if (!runthrough(file, pattern + j, &i, frontend))
			return (true);
		j += count_cmp(pattern + j);
	}
	return (false);
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
