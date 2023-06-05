#include "listft.h"
#include <stdlib.h>

// Deletes a single node from a linked list.
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		if (lst->content)
		{
			del(lst->content);
			free(lst);
		}
		lst = NULL;
	}
}
