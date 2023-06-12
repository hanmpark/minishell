#include "listft.h"

// Adds a new node at the end of a linked list.
void	ft_lstadd_back(t_cmdtable **lst, t_cmdtable *new)
{
	t_cmdtable	*theone;

	if (!*lst)
		*lst = new;
	else
	{
		theone = ft_lstlast(*lst);
		theone->next = new;
	}
}
