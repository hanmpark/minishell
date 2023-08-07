#include "minishell.h"
#include "builtin.h"

/*
* Env command:
* It allows the user to see a list of all environment variables,
* along with their values, that are available in the current session.
*/
int	ft_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
	}
	return (0);
}
