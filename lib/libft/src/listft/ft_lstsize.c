#include "listft.h"

// Counts the number of elements in a linked list.
int	ft_lstsize(t_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
