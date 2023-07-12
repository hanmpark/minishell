#include "structft.h"
#include <stdlib.h>

// Creates a new allocated t_cmd structure
t_cmd	*ft_cmdnew(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->fdin = 0;
	cmd->fdout = 1;
	cmd->par_id = 0;
	cmd->par_last = 0;
	return (cmd);
}
