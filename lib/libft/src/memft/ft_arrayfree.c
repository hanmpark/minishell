#include "memft.h"

void	ft_arrayfree(char **ar)
{
	int	i;

	if (!ar)
		return ;
	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}
