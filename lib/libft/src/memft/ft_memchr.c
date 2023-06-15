#include <stdlib.h>

/* Searches for the first occurrence of a specified byte value
* in a memory block.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	char	ch;
	char	*var;
	int		i;

	ch = (char)c;
	i = 0;
	var = (char *)s;
	while (n--)
	{
		if (var[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
