#include "listft.h"

void	ft_treeadd_right(t_treenode *node, t_treenode *new, int pass)
{
	if (!node)
		return ;
	if (!node->and_branch)
	{
		node->and_branch = new;
		pass = 0;
	}
	if (!node->or_branch)
		return ;
	ft_treeadd_right(node->or_branch, new, 1);
	if (pass)
		ft_treeadd_right(node->and_branch, new, 1);
}
