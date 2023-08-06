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
	cmd->pid = 0;
	cmd->fdin = 0;
	cmd->fdout = 1;
	return (cmd);
}
