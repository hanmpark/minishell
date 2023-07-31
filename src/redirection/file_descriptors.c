#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "exit.h"
#include <fcntl.h>

static int	open_file(char	*filename, int mode)
{
	int	fd;

	fd = -1;
	if (mode == READ)
		fd = open(filename, O_RDONLY);
	else if (mode == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static void	reset_fd(t_cmd *cmd, t_token *l_token)
{
	if (l_token->type == LESS || l_token->type == DLESS)
	{
		if (cmd->fdin != STDIN_FILENO)
		{
			close(cmd->fdin);
			cmd->fdin = STDIN_FILENO;
		}
	}
	else if (l_token->type == GREAT || l_token->type == DGREAT)
	{
		if (cmd->fdout != STDOUT_FILENO)
		{
			close(cmd->fdout);
			cmd->fdout = STDOUT_FILENO;
		}
	}
}

static bool	check_filename(t_token *token)
{
	char	**expanded_token;

	expanded_token = expand_arg(ft_strdup(token->token));
	if (!expanded_token || ft_arraylen(expanded_token) > 1)
	{
		if (expanded_token)
			ft_arrayfree(expanded_token);
		return (error_expand(token->token, ERR_AMB, 1));
	}
	free(token->token);
	token->token = ft_strdup(*expanded_token);
	ft_arrayfree(expanded_token);
	return (true);
}

/* Treats the redirection for the command:
* - before setting the file descriptors, resets them
* - opens file(s) and stores their file descriptors in the command structure
*/
bool	treat_redir(t_cmd *cmd, t_token **l_token)
{
	t_type	type;

	type = (*l_token)->type;
	reset_fd(cmd, *l_token);
	*l_token = (*l_token)->next;
	if (!check_filename(*l_token))
		return (false);
	if (type == LESS)
		cmd->fdin = open_file((*l_token)->token, READ);
	else if (type == DLESS)
		cmd->fdin = here_doc((*l_token)->token);
	else if (type == GREAT)
		cmd->fdout = open_file((*l_token)->token, TRUNC);
	else if (type == DGREAT)
		cmd->fdout = open_file((*l_token)->token, APPEND);
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (error_expand((*l_token)->token, ERR_ENOENT, 1));
	*l_token = (*l_token)->next;
	return (true);
}
