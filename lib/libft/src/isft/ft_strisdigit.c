#include "isft.h"

// Checks in the given string if it only contains digits.
int	ft_strisdigit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}
