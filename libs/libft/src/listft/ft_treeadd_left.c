#include "listft.h"

void	ft_treeadd_left(t_treenode *node, t_treenode *new, int pass)
{
	if (!node)
		return ;
	if (!node->or_branch)
	{
		node->or_branch = new;
		pass = 0;
	}
	if (!node->and_branch)
		return ;
	ft_treeadd_left(node->and_branch, new, 1);
	if (pass)
		ft_treeadd_left(node->or_branch, new, 1);
}
