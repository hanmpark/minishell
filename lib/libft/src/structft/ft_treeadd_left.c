#include "structft.h"

static void	recursive_add_left(t_treenode *node, t_treenode *new)
{
	int	pass;

	pass = 1;
	if (!node || node->initialized)
		return ;
	if (!node->or_branch)
	{
		node->or_branch = new;
		pass = 0;
	}
	recursive_add_left(node->and_branch, new);
	if (pass)
		recursive_add_left(node->or_branch, new);
	node->initialized = 1;
}

// Adds a new node in each node's or_branch
void	ft_treeadd_left(t_treenode **node, t_treenode *new)
{
	if (!*node)
		*node = new;
	else
	{
		ft_treereset(*node);
		recursive_add_left(*node, new);
	}
}
