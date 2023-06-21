#include "minishell.h"

// pwd builtin
void	ft_pwd(t_cmdtable *table)
{
	char	*pwd;

	(void)table;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

/* Note to self:
need to check if pwd has an error message if it fails?
*/