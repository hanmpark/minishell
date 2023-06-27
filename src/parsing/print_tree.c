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
	printf("command = %s\n", node->cmd->args[0]);
	print_tabs(level);
	printf("fdin = %d\n", node->cmd->fdin);
	print_tabs(level);
	printf("fdout = %d\n", node->cmd->fdout);
	print_tabs(level);
	printf("redir_in = %d\n", node->cmd->redir_in);
	print_tabs(level);
	printf("redir_out = %d\n", node->cmd->redir_out);
	print_tabs(level);
	printf("left\n");

	print_tree_rec(node->or_branch, level + 1);
	print_tabs(level);
	printf("right\n");

	print_tree_rec(node->and_branch, level + 1);
	print_tabs(level);
	printf("done\n");
}

/* Prints out the contents of a binary tree structure
* with tabs to make it easier to apprehend.
* Only for debugging purpose.
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
