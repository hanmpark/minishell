#include "minishell.h"
#include "expander.h"
#include <dirent.h>

static char	**get_current_files(void)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**files;

	files = ft_calloc(1, sizeof(char *));
	if (!files)
		return (NULL);
	dir = opendir(".");
	if (!dir)
	{
		ft_arrayfree(files);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		files = ft_arrayadd(files, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}

static int	get_swap_index(char **files, int i)
{
	int	swap;

	swap = i;
	while (files[i])
	{
		if (ft_strcmp(files[swap], files[i]) > 0)
			swap = i;
		i++;
	}
	return (swap);
}

static char	**swap_array_element(char **files, int i, int swap_index)
{
	char	*tmp;

	tmp = ft_strdup(files[i]);
	free(files[i]);
	files[i] = ft_strdup(files[swap_index]);
	free(files[swap_index]);
	files[swap_index] = tmp;
	return (files);
}

static char	**sort_files(char **files)
{
	int		swap_index;
	int		i;

	i = -1;
	while (files[++i])
	{
		swap_index = get_swap_index(files, i);
		files = swap_array_element(files, i, swap_index);
	}
	return (files);
}

// Get the file names of the current directory and sort them
char	**init_entry_files(void)
{
	char	**sorted_files;
	char	**files;

	files = get_current_files();
	if (!files)
		return (NULL);
	sorted_files = sort_files(files);
	return (sorted_files);
}