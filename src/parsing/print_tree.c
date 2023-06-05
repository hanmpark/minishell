#include "minishell.h"

static void	print_tabs(int numtabs)
{
	int	i;

	i = 0;
	while (i < numtabs)
	{
		printf("\t");
		i++;
	}
}

void	print_tree_rec(t_treenode *root, int level)
{
	if (root == NULL)
	{
		print_tabs(level);
		printf("---<empty>---\n");
		return ;
	}
	print_tabs(level);
	printf("values in the node\n");
	print_tabs(level);
	printf("left\n");

	print_tree(root, level + 1);
	print_tabs(level);
	printf("right\n");

	print_tree(root, level + 1);
	print_tabs(level);
	printf("done\n");
}

/*
* Function that will print out the contents of a binary tree structure
* with tabs to make it easier to apprehend.
*/
void	print_tree(t_treenode *root)
{
	print_tree_rec(root, 0);
}
