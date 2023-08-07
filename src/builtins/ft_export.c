#include "minishell.h"
#include "parsing.h"
#include "builtin.h"
#include "exit.h"

static bool	check_env(char *var_name)
{
	int	i;

	i = -1;
	if (!var_name)
		return (true);
	if (var_name[0] && (!ft_isalpha(var_name[0]) && var_name[0] != '_'))
		return (put_error_env(var_name));
	while (var_name[++i] && var_name[i] != '=')
		if (!ft_isenv(var_name[i]) && \
			!(var_name[i] == '+' && var_name[i + 1] && var_name[i + 1] == '='))
			return (put_error_env(var_name));
	return (true);
}

static void	found_var(char **env_var, char *env, bool append)
{
	char	*tmp;

	tmp = NULL;
	if (append == true)
	{
		if (!ft_strchr(*env_var, '='))
		{
			tmp = ft_strdup(*env_var);
			free(*env_var);
			*env_var = ft_strjoin(tmp, "=");
			free(tmp);
		}
		tmp = ft_strjoin(*env_var, ft_strchr(env, '=') + 1);
		free(*env_var);
		*env_var = tmp;
		return ;
	}
	free(*env_var);
	*env_var = ft_strdup(env);
}

static void	not_found_var(char ***envp, char *env, bool append)
{
	char	*tmp;

	tmp = NULL;
	if (append == true)
	{
		tmp = ft_strndup(env, ft_strchr(env, '+') - env);
		*envp = ft_arrayadd(*envp, ft_strjoin(tmp, ft_strchr(env, '=')));
		free(tmp);
		return ;
	}
	*envp = ft_arrayadd(*envp, ft_strdup(env));
}

static void	edit_env_var(char ***envp, char *env)
{
	int		env_name_len;
	int		i;

	env_name_len = ft_strchr(env, '=') - env;
	if (env_name_len > 0 && *(ft_strchr(env, '=') - 1) == '+')
		env_name_len = ft_strchr(env, '+') - env;
	i = -1;
	while ((*envp)[++i])
	{
		if (env_name_len < 0 && !ft_strncmp((*envp)[i], env, ft_strlen(env)))
			return ;
		if (!ft_strncmp((*envp)[i], env, env_name_len))
		{
			found_var(&(*envp)[i], env, *(ft_strchr(env, '=') - 1) == '+');
			return ;
		}
	}
	if (env_name_len < 0)
		not_found_var(envp, env, false);
	else if (!(*envp)[i])
		not_found_var(envp, env, *(ft_strchr(env, '=') - 1) == '+');
}

/*
* Exports variables/print the list of environment variables:
* - if export is used without any argument, displays the list of all
* the environment variables in ASCII ascending order, with "declare -x"
* in front of them.
* - else, it sets and exports environment variables.
*/
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
