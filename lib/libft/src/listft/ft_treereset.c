#include "listft.h"

void	ft_treereset(t_treenode *node)
{
	if (!node)
		return ;
	node->initialized = 0;
	node->depth = 0;
	ft_treereset(node->and_branch);
	ft_treereset(node->or_branch);
}
