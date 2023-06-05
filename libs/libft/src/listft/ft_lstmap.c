#include "listft.h"
#include <stdlib.h>

/* Applies a function to each element of a linked list and creates a new list
* with the modified elements.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*next;

	if (!lst && !f)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		next = ft_lstnew(f(lst->content));
		if (!next)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, next);
		lst = lst->next;
	}
	return (newlst);
}
