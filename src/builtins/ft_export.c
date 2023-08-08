/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:47 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:18:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

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

static int	set_env_name_len(char *env)
{
	int	env_name_len;

	if (!ft_strchr(env, '='))
		return (-1);
	env_name_len = ft_strchr(env, '=') - env;
	if (*(ft_strchr(env, '=') - 1) == '+')
		env_name_len = ft_strchr(env, '+') - env;
	return (env_name_len);
}

static void	edit_env_var(char ***envp, char *env)
{
	int	env_name_len;
	int	i;

	env_name_len = set_env_name_len(env);
	i = -1;
	while ((*envp)[++i])
	{
		if (env_name_len == NO_EQUAL_SIGN \
			&& !ft_strncmp((*envp)[i], env, ft_strlen(env)))
			return ;
		if (!ft_strncmp((*envp)[i], env, env_name_len))
			return (found_var(&(*envp)[i], env, *(ft_strchr(env, '=') - 1) \
				== '+'));
	}
	if (env_name_len == NO_EQUAL_SIGN)
		return (not_found_var(envp, env, false));
	else if (!(*envp)[i])
		return (not_found_var(envp, env, *(ft_strchr(env, '=') - 1) == '+'));
}

/*
* Export command:
* - if export is used without any argument, displays the list of all
* the environment variables in ASCII ascending order, with "declare -x"
* in front of them.
* - else, it sets and exports environment variables.
*/
int	ft_export(char **argv, char ***envp)
{
	int	return_val;
	int	i;

	i = 0;
	return_val = EXIT_SUCCESS;
	while (argv[++i])
	{
		if (!check_env_var(argv[i]))
		{
			return_val = EXIT_FAILURE;
			continue ;
		}
		edit_env_var(envp, argv[i]);
	}
	if (i == 1)
		put_export(*envp);
	return (return_val);
}
