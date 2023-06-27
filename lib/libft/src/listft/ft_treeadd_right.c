#include "listft.h"

static void	recursive_add_right(t_treenode *node, t_treenode *new, int pass)
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
	recursive_add_right(node->or_branch, new, 1);
	if (pass)
		recursive_add_right(node->and_branch, new, 1);
}

void	ft_treeadd_right(t_treenode **node, t_treenode *new)
{
	if (!*node)
		*node = new;
	else
		recursive_add_right(*node, new, 1);
}
