#include "listft.h"
#include <stdbool.h>

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