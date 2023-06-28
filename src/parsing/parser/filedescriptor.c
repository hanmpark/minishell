#include "minishell.h"
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

/* Treats the redirection for the command:
* - treats the entry of the redirection as well (eg: 2>)
* - treats here_doc
* - open the file(s)
*/
t_token	*treat_redir(t_cmd *cmd, t_token *l_token, t_type type)
{
	reset_fd(cmd, l_token);
	l_token = l_token->next;
	if (type == LESS)
		cmd->fdin = open_file(l_token->token, READ);
	else if (type == DLESS)
		cmd->fdin = here_doc(l_token->token);
	else if (type == GREAT)
		cmd->fdout = open_file(l_token->token, TRUNC);
	else if (type == DGREAT)
		cmd->fdout = open_file(l_token->token, APPEND);
	return (l_token->next);
}
