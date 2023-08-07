#include "minishell.h"
#include "parsing.h"
#include "builtin.h"
#include "exit.h"

static void	sort_ascii(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[++j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
		}
	}
}

/*
* Prints out all the environment variables of the current session
* in ASCII ascending order.
*/
void	put_export(char **envp)
{
	int		i;
	char	*env_name;

	i = -1;
	sort_ascii(envp);
	while (envp[++i])
	{
		env_name = ft_strchr(envp[i], '=');
		if (!env_name)
			ft_printf(EXPORTED"%s\n", envp[i]);
		else
		{
			env_name = ft_strndup(envp[i], env_name - envp[i] + 1);
			ft_printf(EXPORTED"%s", env_name);
			ft_printf("\"%s\"\n", envp[i] + ft_strlen(env_name));
			free(env_name);
		}
	}
}
