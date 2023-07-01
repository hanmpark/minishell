#include "structft.h"
#include <stdlib.h>

// Returns the last element of a linked list.
t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
