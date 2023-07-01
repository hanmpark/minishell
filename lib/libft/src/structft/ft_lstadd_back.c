#include "structft.h"

// Adds a new node at the end of a linked list.
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*theone;

	if (!*lst)
		*lst = new;
	else
	{
		theone = ft_lstlast(*lst);
		theone->next = new;
	}
}
