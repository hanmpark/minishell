#include "listft.h"
#include <stdlib.h>

t_treenode	*ft_treenew(t_cmdtable *tokens, int redir)
{
	t_treenode	*node;

	node = malloc(sizeof(t_treenode));
	if (!node)
		return (NULL);
	node->tokens = tokens;
	node->return_val = 0;
	node->redir = redir;
	node->tree = NULL;
	node->or_branch = NULL;
	node->and_branch = NULL;
	return (node);
}
