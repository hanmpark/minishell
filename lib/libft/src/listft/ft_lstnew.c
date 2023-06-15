#include "listft.h"
#include <stdlib.h>

// Creates a new linked list node.
t_cmdtable	*ft_lstnew(char *token, int type)
{
	t_cmdtable	*lst;

	lst = malloc(sizeof(t_cmdtable));
	if (!lst)
		return (NULL);
	lst->token = token;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}
