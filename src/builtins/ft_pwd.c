#include "minishell.h"

// pwd builtin
void	ft_pwd(void)
{
	char	buf[4096];

	if (getcwd(buf, 4096) == NULL)
		return ;
	ft_putendl_fd(buf, 1);
	// need to add 0 value for success command execution: $? = 0
}

/* Note to self:
4096: the length of the working directory is limited to 4096 characters
in certain Linux / macOS systems. Defined by the POSIX standard.

pwd: Failure: need to check if pwd has an error message if it fails?
*/