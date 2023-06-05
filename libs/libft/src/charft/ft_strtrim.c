#include "charft.h"

// Removes specified characters from the beginning and end of a string.
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	dstsize;
	size_t	len;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1 == 0)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	while (s1[len - 1] && ft_strrchr(set, s1[len - 1]))
		len--;
	dstsize = len;
	dest = ft_substr(s1, 0, dstsize);
	return (dest);
}
