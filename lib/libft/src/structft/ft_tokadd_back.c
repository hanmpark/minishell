#include "structft.h"

// Adds a new node at the end of a linked list.
void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*node;

	if (!*lst)
		*lst = new;
	else
	{
		node = ft_toklast(*lst);
		node->next = new;
	}
}
