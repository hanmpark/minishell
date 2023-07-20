#include "structft.h"
#include <stdlib.h>

// Creates a new linked list node.
t_token	*ft_toknew(char *token, int type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->token = token;
	tok->type = type;
	tok->next = NULL;
	tok->par_id = 0;
	return (tok);
}
