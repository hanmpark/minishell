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

static void	print_commands(t_cmd **cmd, int nb_pipe, int level)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		print_tabs(level);
		print_command(cmd[i]->args);
		print_tabs(level);
		printf("fdin = %d\n", cmd[i]->fdin);
		print_tabs(level);
		printf("fdout = %d\n", cmd[i]->fdout);
		print_tabs(level);
		printf("redir_in = %d\n", cmd[i]->redir_in);
		print_tabs(level);
		printf("redir_out = %d\n", cmd[i]->redir_out);
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
	if (node->cmd)
		print_commands(node->cmd, node->nb_pipe, level);
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
	print_tree_rec(node, 0);
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
