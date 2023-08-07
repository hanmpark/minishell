#include "structft.h"

// Adds a new node at the beginning of a linked list.
void	ft_tokadd_front(t_tok **lst, t_tok *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}
