#include "listft.h"
#include <stdlib.h>

t_treenode	*ft_treenew(t_cmd *cmd)
{
	t_treenode	*node;

	node = malloc(sizeof(t_treenode));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->or_branch = NULL;
	node->and_branch = NULL;
	return (node);
}
