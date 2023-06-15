#include "charft.h"
#include <stdlib.h>

// Duplicates n number of bytes in a null-terminated string.
char	*ft_strndup(const char *source, int n)
{
	char	*dest;
	int		count;

	if (n > (int)ft_strlen(source))
		return (NULL);
	else if (n == 0)
		return (ft_strdup(""));
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
