#include "structft.h"

// Counts the number of pipes
int	ft_countpipe(t_tok *l_token)
{
	int	nbr;

	nbr = 1;
	while (l_token && (l_token->type != 2 && l_token->type != 3))
	{
		if (l_token->type == 6)
			nbr++;
		l_token = l_token->next;
	}
	return (nbr);
}
