#include "listft.h"

void	ft_treeset_depth(t_treenode *node)
{
	if (!node)
		return ;
	ft_treeset_depth(node->and_branch);
	ft_treeset_depth(node->or_branch);
	node->depth++;
}
