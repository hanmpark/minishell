#include "libft.h"

// Duplicates a null-terminated string.
char	*ft_strdup(const char *source)
{
	int		i;
	int		count;
	char	*dest;

	i = ft_strlen(source) + 1;
	count = 0;
	dest = malloc(i * sizeof(char));
	if (!dest)
		return (0);
	while (source[count])
	{
		dest[count] = source[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
