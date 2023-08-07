#include "structft.h"
#include <stdlib.h>

// Creates a new linked list node.
t_tok	*ft_toknew(char *token, int type)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	tok->token = token;
	tok->type = type;
	tok->next = NULL;
	tok->par_id = 0;
	return (tok);
}
