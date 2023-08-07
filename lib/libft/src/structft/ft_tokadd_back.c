#include "structft.h"

// Adds a new node at the end of a linked list.
void	ft_tokadd_back(t_tok **lst, t_tok *new)
{
	t_tok	*node;

	if (!*lst)
		*lst = new;
	else
	{
		node = ft_toklast(*lst);
		node->next = new;
	}
}
