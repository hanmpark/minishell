#include "charft.h"
#include <stdlib.h>

/*
* Applies a function to each character of a string,
* creating a new string with the modified characters.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*nstr;

	if (!s)
		return (0);
	nstr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	nstr[i] = 0;
	return (nstr);
}
