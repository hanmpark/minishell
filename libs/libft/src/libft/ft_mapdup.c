#include "libft.h"

static int	maplen(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

// Duplicates an array of strings
char	**ft_mapdup(char **map)
{
	char	**res;
	int		i;

	i = -1;
	res = malloc((maplen(map) + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (map && map[++i])
		res[i] = ft_strdup(map[i]);
	res[i] = 0;
	return (res);
}
