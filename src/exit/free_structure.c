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

void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i]->fdin != STDIN_FILENO && cmd[i]->fdin != -1)
			close(cmd[i]->fdin);
		if (cmd[i]->fdout != STDOUT_FILENO && cmd[i]->fdout != -1)
			close(cmd[i]->fdout);
		ft_arrayfree(cmd[i]->args);
		free(cmd[i]);
		i++;
	}
	if (cmd)
		free(cmd);
}

static void	free_node(t_treenode **node)
{
	if (!(*node))
		return ;
	free_node(&(*node)->and_branch);
	free_node(&(*node)->or_branch);
	if ((*node)->rec_cycles == 1)
	{
		free_cmd((*node)->cmd);
		free(*node);
		*node = NULL;
	}
	else
		(*node)->rec_cycles--;
}

void	free_tree(t_treenode *tree)
{
	if (!tree)
		return ;
	ft_treeset_cycles(tree);
	free_node(&tree);
}
