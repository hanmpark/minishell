#include "charft.h"

// Counts the lenght of an array
int	ft_arraylen(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}
