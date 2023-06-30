#include "listft.h"
#include <stdlib.h>

t_treenode	*ft_treenew(t_cmd *cmd)
{
	t_treenode	*node;

	node = malloc(sizeof(t_treenode));
	if (!node)
		return (NULL);
	node->depth = 1;
	node->initialized = 0;
	node->cmd = cmd;
	node->or_branch = NULL;
	node->and_branch = NULL;
	return (node);
}
