#include "listft.h"

// Adds a new node at the end of a linked list.
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*theone;

	if (!*lst)
		*lst = new;
	else
	{
		theone = ft_lstlast(*lst);
		theone->next = new;
	}
}
