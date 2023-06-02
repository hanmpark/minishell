#include "libft.h"

// Compares two memory blocks up to a specified number of bytes.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str1;
	int				i;

	str = (unsigned char *)s1;
	str1 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str[i] != str1[i])
			return ((str[i] - str1[i]));
		i++;
	}
	return (0);
}
