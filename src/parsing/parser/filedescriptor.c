#include "minishell.h"
#include "expander.h"
#include "parsing.h"
#include "fcntl.h"
#include "error.h"

static int	open_file(char	*filename, int mode)
{
	int fd;

	fd = -1;
	if (mode == READ)
		fd = open(filename, O_RDONLY);
	else if (mode == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static int	check_fd(char *token)
{
	char	*tmp;
	int		fd;
	int		i;

	if (!ft_isdigit(*token))
		return (-1);
	i = 0;
	while (token[i] && !is_redir(is_separator(token + i)))
		i++;
	tmp = ft_substr(token, 0, i);
	fd = ft_atoi(tmp); // have to review atoi (if input is > MAX_INT)
	free(tmp);
	return (fd);
}

static void	reset_fd(t_cmd *cmd, t_token *l_token)
{
	if (l_token->type == LESS || l_token->type == DLESS)
	{
		if (cmd->fdin != STDIN_FILENO)
			close(cmd->fdin);
		cmd->redir_in = check_fd(l_token->token);
	}
	else if (l_token->type == GREAT || l_token->type == DGREAT)
	{
		if (cmd->fdout != STDOUT_FILENO)
			close(cmd->fdout);
		cmd->redir_out = check_fd(l_token->token);
	}
}

static bool	check_filename(char *filename)
{
	char	*tmp;

	tmp = expand_arg(ft_strdup(filename));
	if (!tmp || ft_foundspace(tmp))
	{
		if (tmp)
			free(tmp);
		return (error_expand(filename, ERR_AMB, 1));
	}
	free(tmp);
	return (true);
}

/* Treats the redirection for the command:
* - treats the entry of the redirection as well (eg: 2>)
* - treats here_doc
* - open the file(s)
*/
bool	treat_redir(t_cmd *cmd, t_token **l_token, t_type type)
{
	reset_fd(cmd, *l_token);
	*l_token = (*l_token)->next;
	if (!check_filename((*l_token)->token))
		return (false);
	(*l_token)->token = expand_arg((*l_token)->token);
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
