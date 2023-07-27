#include "charft.h"

// Calculates the length of a null-terminated string.
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
