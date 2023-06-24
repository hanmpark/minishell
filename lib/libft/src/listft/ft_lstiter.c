#include "listft.h"

// Applies a function to each element of a linked list.
void	ft_lstiter(t_token *lst, void (*f)(void *))
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
