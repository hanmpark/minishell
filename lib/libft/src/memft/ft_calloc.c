#include "memft.h"
#include <limits.h>

/* Allocates a block of memory for an array and initializes all the bytes
* to zero.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*var;

	if (count > UINT_MAX)
		return (NULL);
	var = malloc(count * size);
	if (!var)
		return (NULL);
	ft_bzero(var, count * size);
	return (var);
}
