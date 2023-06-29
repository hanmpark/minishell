#include "charft.h"
#include "memft.h"

static void	array_cpy(char **dest, char **source, int start)
{
	int	i;

	i = -1;
	while (source[++i])
		dest[start++] = ft_strdup(source[i]);
}

char	**ft_arrayjoin(char **ar1, char **ar2)
{
	char	**dest;
	int		destsize;

	if (!ar1 || !ar2)
		return (NULL);
	destsize = ft_arraylen(ar1) + ft_arraylen(ar2);
	dest = ft_calloc(ft_arraylen(ar1) + ft_arraylen(ar2) + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	array_cpy(dest, ar1, 0);
	array_cpy(dest, ar2, ft_arraylen(ar1));
	ft_arrayfree(ar1);
	ft_arrayfree(ar2);
	return (dest);
}
