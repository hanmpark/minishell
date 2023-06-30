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

void	free_node(t_treenode **node)
{
	if (!(*node))
		return ;
	free_node(&(*node)->and_branch);
	free_node(&(*node)->or_branch);
	if ((*node)->depth == 1)
	{
		if ((*node)->cmd->fdin != STDIN_FILENO && (*node)->cmd->fdin != -1)
			close((*node)->cmd->fdin);
		if ((*node)->cmd->fdout != STDOUT_FILENO && (*node)->cmd->fdout != -1)
			close((*node)->cmd->fdout);
		ft_arrayfree((*node)->cmd->args);
		(*node)->cmd->args = NULL;
		free((*node)->cmd);
		(*node)->cmd = NULL;
		free(*node);
		*node = NULL;
	}
	else
		(*node)->depth--;
}

void	free_tree(t_treenode **tree)
{
	int	i;

	i = -1;
	while (tree && tree[++i])
		free_node(&tree[i]);
	if (tree)
		free(tree);
}
