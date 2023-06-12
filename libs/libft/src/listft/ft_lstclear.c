#include "listft.h"
#include <stdlib.h>

// Deletes and frees all the nodes in a linked list.
void	ft_lstclear(t_cmdtable **lst, void (*del)(void *))
{
	t_cmdtable	*current;
	t_cmdtable	*next;

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
