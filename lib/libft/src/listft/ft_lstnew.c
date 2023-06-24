#include "listft.h"
#include <stdlib.h>

// Creates a new linked list node.
t_token	*ft_lstnew(char *token, int type)
{
	t_token	*lst;

	lst = malloc(sizeof(t_token));
	if (!lst)
		return (NULL);
	lst->token = token;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}
