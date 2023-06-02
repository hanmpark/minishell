#include "libft.h"

// Sets a specified number of bytes in a memory block to a given value.
void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;

	str = b;
	while (len)
	{
		*str++ = c;
		len--;
	}
	return (b);
}
