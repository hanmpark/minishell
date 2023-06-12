#include "listft.h"
#include <stdbool.h>

static void	recursive_add_left(t_treenode *node, t_treenode *new, bool right)
{
	if (!node->left)
		node->left = new;
}

void	ft_treeadd_left(t_treenode *tree, t_treenode *new, bool right)
{
	if (!tree || !new)
		return ;
	if (!tree->left)
		tree->left = new;
	if (right && tree->right)
	{
		ft_treeadd_left(tree->right, new, true);
		right = false;
	}
	if (!right && tree->left)
		ft_treeadd_left();
	else if ((right && !tree->right) || (!right && !tree->left))
		return ;
}
