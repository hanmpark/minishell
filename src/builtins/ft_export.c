#include "minishell.h"
#include "parsing.h"
#include "builtin.h"

void	put_export(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_printf("%s%s\n", EXPORTED, envp[i]);
}

char	**invalid_id(char *env_name)
{
	ft_printf("minishell: export: `%s': %s\n", env_name, INVALID_ID);
	return (0);
}

char	**var_creation(char **envp, char *name, char *env_var)
{
	bool	create;
	char	*env_name;
	int		i;

	i = -1;
	create = true;
	if (name)
	{
		printf("\033[30mVAR CREATION\033[0m\n");
		env_name = ft_strndup(env_var, name - env_var);
		ft_printf("env_name: %s\n", env_name);
		if (env_name && !ft_isalpha(env_name[0]))
			return (invalid_id(env_name));
	}
	while (envp[++i])
	{
		ft_printf("envp[%d]\n", i);
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
		{
			ft_printf("ouui\n");
			//free(envp[i]);
			envp[i] = ft_strdup(env_var);
			create = false;
			break ;
		}
	}
	if (create == true)
	{
		envp = ft_arrayadd(envp, ft_strdup(env_var));
		put_export(envp);
	}
	return (envp);
}

int	ft_export(char **av, char **envp)
{
	char	*env_name;
	int		i;

	printf("\033[31mFT_EXPORT:\033[0m\n");
	i = 0;
	while (av[++i])
	{
		env_name = ft_strchr(av[i], '=');
		printf("\033[32menv_name: %s\033[0m\n", env_name);
		envp = var_creation(envp, env_name, av[i]);
	}
	if (i == 1)
		put_export(envp);
	return (0);
}
