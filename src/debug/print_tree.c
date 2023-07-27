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

static void	print_single_cmd(char **args)
{
	int	i;

	if (!args)
	{
		printf("NULL\n");
		return ;
	}
	printf("command = ");
	i = 0;
	while (args[i])
	{
		printf("[%s] ", args[i]);
		fflush(stdout);
		i++;
	}
	printf("\n");
}

static void	print_cmds(t_cmd **cmd, int nb_pipe, int level)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		print_tabs(level);
		print_single_cmd(cmd[i]->args);
		print_tabs(level);
		printf("fdin = %d\n", cmd[i]->fdin);
		print_tabs(level);
		printf("fdout = %d\n", cmd[i]->fdout);
		i++;
		if (i < nb_pipe)
			printf("----- PIPE -----\n");
	}
}

static void	print_tree_rec(t_treenode *node, int level)
{
	if (node == NULL)
	{
		print_tabs(level);
		printf("---<empty>---\n");
		return ;
	}
	if (node->cmd)
		print_cmds(node->cmd, node->nb_pipe, level);
	print_tabs(level);
	printf("rec_cycles = %d\n", node->rec_cycles);
	print_tabs(level);
	printf("par_id = %d\n", node->par_id);
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
void	print_tree(t_treenode *node)
{
	printf("\n\033[38;5;62mTREE:\033[0m\n");
	print_tree_rec(node, 0);
	printf("\n");
	printf("\033[38;5;182mCOMMAND OUTPUT:\033[0m\n");
}
