#include "isft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' \
		|| c == '\f');
}
