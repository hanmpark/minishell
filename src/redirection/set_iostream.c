#include "minishell.h"
#include "execution.h"

static bool	set_redirection(t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		dup2(cmd->fdin, STDIN_FILENO);
		close(cmd->fdin);
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		dup2(cmd->fdout, STDOUT_FILENO);
		close(cmd->fdout);
		return (true);
	}
	return (false);
}

/* Sets the I/O stream for the next command:
* - if there is/are redirection(s) in the command line, sets them in priority
* - else sets the pipe as the I/O stream
* - the last command is not piped
*/
void	set_iostream(t_cmd *cmd, bool is_last)
{
	if (!is_last)
		close(cmd->pipe[READ_END]);
	if (!set_redirection(cmd) && !is_last)
		dup2(cmd->pipe[WRITE_END], STDOUT_FILENO);
	if (!is_last)
		close(cmd->pipe[WRITE_END]);
}
