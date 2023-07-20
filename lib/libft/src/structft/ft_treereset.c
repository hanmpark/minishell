#include "structft.h"

// Resets the count in every node in the tree
void	ft_treereset(t_treenode *node)
{
	if (!node)
		return ;
	node->initialized = 0;
	ft_treereset(node->and_branch);
	ft_treereset(node->or_branch);
}
