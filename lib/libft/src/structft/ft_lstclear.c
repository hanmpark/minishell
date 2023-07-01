#include "structft.h"
#include <stdlib.h>

// Deletes and frees all the nodes in a linked list.
void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*current;
	t_token	*next;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			ft_lstdelone(current, del);
			current = next;
		}
		*lst = NULL;
	}
}
