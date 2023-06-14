#include "charft.h"
#include <stdlib.h>

// Duplicates n number of bytes in a null-terminated string.
char	*ft_strndup(const char *source, int n)
{
	char	*dest;
	int		count;

	if (n > (int)ft_strlen(source) || n == 0)
		return (NULL);
	dest = malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	count = 0;
	while (count < n)
	{
		dest[count] = source[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
