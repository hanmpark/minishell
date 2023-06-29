#include "isft.h"

// Checks if in the given str there is at least a space.
int	ft_foundspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}
