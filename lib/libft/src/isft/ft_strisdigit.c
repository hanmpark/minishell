#include "isft.h"

int	ft_strisdigit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}
