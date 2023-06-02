#include "libft.h"

// Frees each substring and the array of strings itself
void	ft_freestr_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array)
	{
		while (str_array && str_array[i])
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
}
