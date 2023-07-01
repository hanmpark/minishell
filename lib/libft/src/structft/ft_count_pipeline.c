#include "structft.h"

// Counts the number of pipelines there is in the prompt
unsigned int	ft_count_pipeline(t_token *l_token)
{
	unsigned int	nbr;

	nbr = 0;
	while (l_token)
	{
		if (l_token->type == 6)
			nbr++;
		l_token = l_token->next;
	}
	return (nbr + 1);
}
