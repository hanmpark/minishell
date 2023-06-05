#include "listft.h"
#include <stdlib.h>

// Returns the last element of a linked list.
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
