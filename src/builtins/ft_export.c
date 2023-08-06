#include "minishell.h"
#include "parsing.h"
#include "builtin.h"

void	put_invalid(char **invalid)
{
	int	i;

	i = -1;
	while (invalid[++i])
		ft_printf("minishell: export: `%s': not a valid identifier\n", \
			invalid[i]);
	ft_arrayfree(invalid);
}

void	sort_ascii(char **envp)
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

void	put_export(char **envp)
{
	int	i;

	i = -1;
	sort_ascii(envp);
	while (envp[++i])
		ft_printf(EXPORTED"%s\n", envp[i]);
}

void	var_creation(char ***envp, char *name, char *env_var, char **invalid)
{
	char	*env_name;
	bool	create;
	int		i;

	i = -1;
	create = true;
	if (name)
	{
		env_name = ft_strndup(env_var, name - env_var);
		if (env_name && !ft_isalpha(env_name[0]))
		{
			invalid = ft_arrayadd(invalid, ft_strdup(env_name));
			free(env_name);
			return ;
		}
	}
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], name, ft_strlen(name)))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(env_var);
			create = false;
			break ;
		}
	}
	if (create == true)
		*envp = ft_arrayadd(*envp, ft_strdup(env_var));
}

int	ft_export(char **av, char ***envp)
{
	char	**invalid;
	char	*env_name;
	int		i;

	i = 0;
	invalid = NULL;
	while (av[++i])
	{
		env_name = ft_strchr(av[i], '=');
		var_creation(envp, env_name, av[i], invalid);
	}
	if (i == 1)
		put_export(*envp);
	if (invalid)
		put_invalid(invalid);
	return (0);
}
