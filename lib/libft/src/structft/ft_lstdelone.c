#include "structft.h"
#include <stdlib.h>

// Deletes a single node from a linked list.
void	ft_lstdelone(t_token *lst, void (*del)(void *))
{
	if (lst && del)
	{
		if (lst->token)
		{
			del(lst->token);
			free(lst);
		}
		lst = NULL;
	}
}
