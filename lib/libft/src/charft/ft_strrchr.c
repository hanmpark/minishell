#include "charft.h"

// Searches for the last occurrence of a specified character in a string.
char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	if (!c || c == 1024)
		return ((char *)s + ft_strlen(s));
	ptr = NULL;
	while (*s && (char)c)
	{
		if (*s == (char)c)
			ptr = ((char *)s);
		s++;
	}
	return (ptr);
}
