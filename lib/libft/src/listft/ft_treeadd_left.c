#include "listft.h"

static void	recursive_add_left(t_treenode *node, t_treenode *new, int pass)
{
	if (!node)
		return ;
	if (!node->or_branch)
	{
		node->or_branch = new;
		new->ref_count++;
		pass = 0;
	}
	if (!node->and_branch)
		return ;
	recursive_add_left(node->and_branch, new, 1);
	if (pass)
		recursive_add_left(node->or_branch, new, 1);
}

void	ft_treeadd_left(t_treenode **node, t_treenode *new)
{
	if (!*node)
		*node = new;
	else
	{
		new->ref_count = 0;
		recursive_add_left(*node, new, 1);
	}
}
