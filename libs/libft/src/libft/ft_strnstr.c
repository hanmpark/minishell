#include "libft.h"

/* Searches for a substring within a given string,
* but with a specified maximum length to search.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		if (!(ft_strncmp((char *)haystack + i, (char *)needle,
					ft_strlen(needle))))
		{
			if (ft_strlen(needle) + i > len)
				return (NULL);
			return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
