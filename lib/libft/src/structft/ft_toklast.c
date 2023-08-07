#include "structft.h"
#include <stdlib.h>

// Returns the last element of a linked list.
t_tok	*ft_toklast(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
