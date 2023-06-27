#include "minishell.h"
#include "parsing.h"
#include "fcntl.h"
#include "error.h"

static int	open_file(char	*filename, int mode)
{
	int fd;

	fd = -1;
	if (mode == 0)
		fd = open(filename, O_RDONLY);
	else if (mode == 1)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == 2)
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

void	close_fd(int fd, int *redir, bool in)
{
	if (in)
		if (fd != STDIN_FILENO)
			close(fd);
	if (!in)
		if (fd != STDOUT_FILENO)
			close(fd);
	*redir = -1;
}

/* Treats the redirection for the command:
* - treats the entry of the redirection as well (eg: 2>)
* - treats here_doc
* - open the file(s)
*/
void	treat_redir(t_cmd *cmd, t_token *cur, t_token *redir, t_type type)
{
	if (type == LESS || type == DLESS)
	{
		close_fd(cmd->fdin, &cmd->redir_in, true);
		cmd->redir_in = check_fd(redir->token);
	}
	else if (type == GREAT || type == DGREAT)
	{
		close_fd(cmd->fdout, &cmd->redir_out, false);
		cmd->redir_out = check_fd(redir->token);
	}
	if (type == LESS)
		cmd->fdin = open_file(cur->token, 0);
	else if (type == DLESS)
		cmd->fdin = here_doc(cur->token);
	else if (type == GREAT)
		cmd->fdout = open_file(cur->token, 1);
	else if (type == DGREAT)
		cmd->fdout = open_file(cur->token, 2);
}
