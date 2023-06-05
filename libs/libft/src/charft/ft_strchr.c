#include "charft.h"

// Searches for the first occurrence of a specified character in a string.
char	*ft_strchr(const char *s, int c)
{
	if (!c || c == 1024)
		return ((char *)s + ft_strlen(s));
	while (*s && (char)c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}
