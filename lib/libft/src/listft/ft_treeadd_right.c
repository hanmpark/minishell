#include "listft.h"

static void	recursive_add_right(t_treenode *node, t_treenode *new)
{
	int	pass;

	pass = 1;
	if (!node || node->tree_done)
		return ;
	if (!node->and_branch)
	{
		node->and_branch = new;
		pass = 0;
	}
	recursive_add_right(node->or_branch, new);
	if (pass)
		recursive_add_right(node->and_branch, new);
	node->tree_done = 1;
}

void	ft_treeadd_right(t_treenode **node, t_treenode *new)
{
	if (!*node)
		*node = new;
	else
	{
		ft_treereset_depth(*node);
		new->depth = 0;
		recursive_add_right(*node, new);
		ft_treeset_depth(*node);
	}
}
