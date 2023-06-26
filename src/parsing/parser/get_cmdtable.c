#include "minishell.h"
#include "parsing.h"
#include "error.h"

static int	count_pipeline(t_token	*l_token)
{
	int	nbr;

	nbr = 0;
	while (l_token)
	{
		if (l_token->type == PIPE)
			nbr++;
		l_token = l_token->next;
	}
	return (nbr + 1);
}

static t_token	*next_pipeline(t_token *l_token)
{
	while (l_token && l_token->type != PIPE)
		l_token = l_token->next;
	if (l_token)
		return (l_token->next);
	return (l_token);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	return (cmd);
}

/* ✨ CAREFUL ✨
* The following code is bullshit, have to code it again
*/
static t_cmd	*get_cmd(t_token *l_token, t_treenode *cur_node)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL); // Maybe for parsing errors it is better to exit()
	while (l_token && l_token->type != PIPE)
	{
		if (is_redir(l_token->type))
			treat_redir(cmd, l_token->next, l_token->type);
		else if (l_token->type == AND_IF)
			ft_treeadd_right(cur_node, );
		else
			cmd->args = get_args(&l_token);
		l_token = l_token->next;
	}
	return (cmd);
}

/* Get the command table for the execution part:
* - treats redirections for commands
* - creates a tree node for each pipeline
*/
t_treenode	**get_cmdtable(t_token *l_token)
{
	t_treenode	**cmdtable;
	int			nb_pipeline;
	int			i;

	nb_pipeline = count_pipeline(l_token);
	cmdtable = ft_calloc(nb_pipeline + 1, sizeof(t_treenode *));
	if (!cmdtable)
		return (NULL);
	i = 0;
	while (i < nb_pipeline)
	{
		cmdtable[i]->cmd = get_cmd(l_token, cmdtable[i]);
		if (!cmdtable[i]->cmd)
		{
			free_tree(cmdtable);
			return (NULL);
		}
		l_token = next_pipeline(l_token);
		i++;
	}
	return (cmdtable);
}
