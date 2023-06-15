#include "isft.h"

// Checks if a given character is part of a env_var
int	ft_isenv(char c)
{
	return (ft_isalnum(c) || c == '_');
}
