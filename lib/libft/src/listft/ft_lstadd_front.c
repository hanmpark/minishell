#include "listft.h"

// Adds a new node at the beginning of a linked list.
void	ft_lstadd_front(t_cmdtable **lst, t_cmdtable *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}