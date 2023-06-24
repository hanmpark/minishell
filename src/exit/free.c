#include "minishell.h"

void	free_tokens(t_token **l_token)
{
	t_token	*current;
	t_token	*next;

	if (!*l_token)
		return ;
	current = *l_token;
	while (current)
	{
		next = current->next;
		free(current->token);
		current->token = NULL;
		free(current);
		current = next;
	}
	*l_token = NULL;
}

void	free_array(char **args)
{
	int	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_node(t_treenode *tree)
{
	if (!tree)
		return ;
	free_node(tree->or_branch);
	free_node(tree->and_branch);
	free_array(tree->cmd->args);
	tree->cmd->args = NULL;
	if (fdin != STDIN_FILENO && fdin != -1)
		close(fdin);
	if (fdout != STDOUT_FILENO && fdout != -1)
		close(fdout);
	free(tree->cmd);
	tree->cmd = NULL;
	if (tree->cmd->hdoc)
		free(tree->cmd->hdoc);
}

void	free_tree(t_treenode **tree)
{
	int	i;

	i = 0;
	while (tree && tree[i])
	{
		free_node(tree[i]);
		i++;
	}
}
