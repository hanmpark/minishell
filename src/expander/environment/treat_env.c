/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:15 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 18:41:25 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "isft.h"

extern int	g_sig;

char	*get_env(char *str, char **envp)
{
	size_t	env_name_len;
	char	*env;
	int		i;

	i = 0;
	while (str[i] && ft_isenv(str[i]))
		i++;
	env = ft_substr(str, 0, i);
	env_name_len = ft_strlen(env);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], env, env_name_len))
		{
			free(env);
			return (envp[i] + env_name_len + 1);
		}
	}
	free(env);
	return (NULL);
}

static char	*replace_env(char *line, char *replace, bool exit, int start)
{
	char	*tmp;
	char	*edited_line;

	edited_line = ft_substr(line, 0, start);
	tmp = ft_strjoin(edited_line, replace);
	free(edited_line);
	start++;
	if (exit)
		start++;
	else
		while (line[start] && (ft_isenv(line[start])))
			start++;
	edited_line = ft_strjoin(tmp, line + start);
	free(tmp);
	return (edited_line);
}

static char	*edit_line(char *line, char *env, char **envp, int *i)
{
	char	*env_value;
	char	*edited_line;

	env_value = get_env(env, envp);
	if (!env_value)
		edited_line = replace_env(line, "", false, *i);
	else
	{
		edited_line = replace_env(line, env_value, false, *i);
		*i += (int)ft_strlen(env_value) - 1;
	}
	free(line);
	return (edited_line);
}

static char	*edit_line_exit(char *line, char *exit_st, int *i)
{
	char	*edited_line;

	edited_line = replace_env(line, exit_st, true, *i);
	*i += (int)ft_strlen(exit_st) - 1;
	free(exit_st);
	free(line);
	return (edited_line);
}

/*
* Treats the environment variable(s):
* - if the environment variable exists, replace it by its value.
* - else, deletes it from the line.
*/
char	*treat_env(t_mnsh *mnsh, char *line, bool prevent_eval)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isenv(line[i + 1]) || prevent_eval))
			line = edit_line(line, line + i + 1, mnsh->envp, &i);
		else if (line[i] == '$' && line[i + 1] && line[i + 1] == '?')
			line = edit_line_exit(line, ft_itoa(g_sig), &i);
		else
			i++;
	}
	return (line);
}
