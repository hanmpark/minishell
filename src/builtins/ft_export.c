#include "minishell.h"
#include "parsing.h"
#include "builtin.h"

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

bool	put_error_env(char *var_name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (false);
}

bool	check_env(char *var_name)
{
	int	i;

	i = -1;
	if (!var_name)
		return (true);
	if (var_name[0] && (!ft_isalpha(var_name[0]) && var_name[0] != '_'))
		return (put_error_env(var_name));
	while (var_name[++i] && var_name[i] != '=')
		if (!ft_isenv(var_name[i]))
			return (put_error_env(var_name));
	return (true);
}

void	edit_env_var(char ***envp, char *env)
{
	bool	create;
	int		env_name_len;
	int		i;

	create = true;
	env_name_len = ft_strchr(env, '=') - env;
	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], env, env_name_len))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(env);
			create = false;
			break ;
		}
	}
	if (create == true)
		*envp = ft_arrayadd(*envp, ft_strdup(env));
}

int	ft_export(char **av, char ***envp)
{
	int	return_val;
	int	i;

	i = 0;
	return_val = 0;
	while (av[++i])
	{
		if (!check_env(av[i]))
		{
			return_val = 1;
			continue ;
		}
		edit_env_var(envp, av[i]);
	}
	if (i == 1)
		put_export(*envp);
	return (return_val);
}
