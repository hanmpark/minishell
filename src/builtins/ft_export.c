#include "minishell.h"
#include "parsing.h"

char	**find_or_create_var(char **envp, char *name, char *env_var)
{
	bool	create;
	char	*env_name;
	int		i;

	i = -1;
	create = true;
	if (name)
		env_name = ft_strndup(env_var, name - env_var);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)))
		{
			free(envp[i]);
			envp[i] = ft_strdup(env_var);
			create = false;
			break ;
		}
	}
	if (create == true)
		envp = ft_arrayadd(envp, ft_strdup(env_var));
	free(name);
	return (envp);
}

void	ft_export(char **av, char **envp)
{
	int		i;
	char	*line;
	char	*env_name;

	i = 0;
	while (av[++i])
	{
		env_name = ft_strchr(av[i], '=');
		g_ms.env_var = find_or_create_var(g_ms.env_var, env_name, av[i]);
	}
	if (i == 1)
		print_export();
}
