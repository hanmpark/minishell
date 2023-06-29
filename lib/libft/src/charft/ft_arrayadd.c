#include "charft.h"
#include "memft.h"

char	**ft_arrayadd(char **ar, char *add)
{
	char	**new_ar;

	new_ar = ft_calloc(2, sizeof(char *));
	if (!new_ar)
		return (NULL);
	*new_ar = add;
	new_ar = ft_arrayjoin(ar, new_ar);
	return (new_ar);
}
