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

void	print_tree_rec(t_treenode *node, int level)
{
	if (node == NULL)
	{
		print_tabs(level);
		printf("---<empty>---\n");
		return ;
	}
	print_tabs(level);
	printf("node->fdin = %d\n", node->cmd->fdin);
	print_tabs(level);
	printf("node->fdout = %d\n", node->cmd->fdout);
	print_tabs(level);
	printf("node->redir_in = %d\n", node->cmd->redir_in);
	print_tabs(level);
	printf("node->redir_out = %d\n", node->cmd->redir_out);
	print_tabs(level);
	printf("left\n");

	print_tree_rec(node->or_branch, level + 1);
	print_tabs(level);
	printf("right\n");

	print_tree_rec(node->and_branch, level + 1);
	print_tabs(level);
	printf("done\n");
}

/*
* Function that will print out the contents of a binary tree structure
* with tabs to make it easier to apprehend.
*/
void	print_tree(t_treenode **node)
{
	int	i;

	i = 0;
	printf("PASS\n");
	while (node[i])
	{
		printf("--- TREE N%d ---\n", i);
		print_tree_rec(node[i], 0);
		i++;
	}
}
