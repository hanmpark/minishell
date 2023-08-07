#include "structft.h"

// Counts how many times it has to pass in a node to run through the whole tree
void	ft_treeset_cycles(t_tree *node)
{
	if (!node)
		return ;
	ft_treeset_cycles(node->and_branch);
	ft_treeset_cycles(node->or_branch);
	node->rec_cycles++;
}
