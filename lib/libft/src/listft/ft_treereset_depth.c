#include "listft.h"

void	ft_treereset_depth(t_treenode *node)
{
	if (!node)
		return ;
	node->tree_done = 0;
	ft_treereset_depth(node->and_branch);
	ft_treereset_depth(node->or_branch);
}
