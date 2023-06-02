#include "libft.h"

// Sets a specified block of memory to zero by writing null bytes.
void	ft_bzero(void *s, size_t n)
{
	char	*var;

	var = s;
	while (n)
	{
		*var++ = 0;
		n--;
	}
}
