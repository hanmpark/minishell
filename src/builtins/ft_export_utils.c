/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:49:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "builtin.h"
#include "putft.h"
#include "isft.h"

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

static bool	put_error_export(char *var_name)
{
	ft_putstr_fd(ERR_EXPORT, 2);
	ft_putstr_fd(var_name, 2);
	ft_putstr_fd(NOT_VALID_ID, 2);
	return (false);
}

bool	check_env_var(char *var_name)
{
	int	i;

	i = -1;
	if (!*var_name)
		return (put_error_export(var_name));
	if (var_name[0] && (!ft_isalpha(var_name[0]) && var_name[0] != '_'))
		return (put_error_export(var_name));
	while (var_name[++i] && var_name[i] != '=')
		if (!ft_isenv(var_name[i]) && \
			!(var_name[i] == '+' && var_name[i + 1] && var_name[i + 1] == '='))
			return (put_error_export(var_name));
	return (true);
}
