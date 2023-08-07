#include "minishell.h"
#include "builtin.h"
#include "exit.h"

static void	sort_ascii(char **envp)
{
	char	*tmp;
	int		i;
	int		j;

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
	char	*env_name;
	int		i;

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

bool	check_env_var(char *var_name)
{
	int	i;

	i = -1;
	if (!*var_name)
		return (put_error_env(var_name));
	if (var_name[0] && (!ft_isalpha(var_name[0]) && var_name[0] != '_'))
		return (put_error_env(var_name));
	while (var_name[++i] && var_name[i] != '=')
		if (!ft_isenv(var_name[i]) && \
			!(var_name[i] == '+' && var_name[i + 1] && var_name[i + 1] == '='))
			return (put_error_env(var_name));
	return (true);
}
