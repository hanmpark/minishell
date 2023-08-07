#include "minishell.h"
#include "builtin.h"
#include "exit.h"

static bool	check_unset_arg(char *arg)
{
	int	i;

	i = -1;
	if (!*arg)
		return (put_error_env(arg));
	if (arg[0] && (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (put_error_env(arg));
	while (arg[++i])
		if (!ft_isenv(arg[i]))
			return (put_error_env(arg));
	return (true);
}

static char	**update_envp(char *env_var, size_t cmplen, char **envp)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = ft_calloc(ft_arraylen(envp), sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = -1;
	j = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(env_var, envp[i], cmplen))
			continue ;
		new_envp[++j] = ft_strdup(envp[i]);
	}
	ft_arrayfree(envp);
	return (new_envp);
}

static char	**unset_variable(char *arg, char **envp)
{
	size_t	cmplen;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
			cmplen = ft_strchr(envp[i], '=') - envp[i];
		else
			cmplen = ft_strlen(envp[i]);
		if (!ft_strncmp(envp[i], arg, cmplen))
			return (update_envp(envp[i], cmplen, envp));
	}
	return (envp);
}

/*
* Unset command:
* It is used to remove/unset environment variables from the current
* session.
*/
int	ft_unset(char **argv, char ***envp)
{
	int	return_val;
	int	i;

	i = 0;
	return_val = EXIT_SUCCESS;
	while (argv[++i])
	{
		if (!check_unset_arg(argv[i]))
		{
			return_val = EXIT_FAILURE;
			continue ;
		}
		*envp = unset_variable(argv[i], *envp);
	}
	return (return_val);
}
