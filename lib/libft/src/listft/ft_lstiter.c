#include "listft.h"

// Applies a function to each element of a linked list.
void	ft_lstiter(t_cmdtable *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->token);
			lst = lst->next;
		}
	}
}
