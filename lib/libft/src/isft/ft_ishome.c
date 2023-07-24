#include "isft.h"

// Checks if the str is HOME (~)
int	ft_ishome(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] != '~')
		return (0);
	i++;
	while (str && str[i])
	{
		if (str[i] != '/')
			return (0);
		i++;
	}
	return (1);
}
