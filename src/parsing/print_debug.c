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

static void	print_command(char **args)
{
	int	i;

	if (!args)
		return ;
	printf("command = ");
	i = 0;
	while (args[i])
	{
		printf("[%s] ", args[i]);
		i++;
	}
	printf("\n");
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
	if (node->cmd->args)
		print_command(node->cmd->args);
	else
		printf("command = NULL\n");
	print_tabs(level);
	printf("depth = %d\n", node->depth);
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
	while (node[i])
	{
		printf("--- TREE N%d ---\n", i);
		print_tree_rec(node[i], 0);
		i++;
	}
}

// Prints out the tokens with their type (ONLY FOR DEBUG PURPOSE)
void	print_tokens(t_token *l_token)
{
	int	count;

	count = 0;
	while (l_token)
	{
		printf("[%d] token = [%s] type = %d\n", count, l_token->token, l_token->type);
		l_token = l_token->next;
		count++;
	}
	printf("\n\n");
}
