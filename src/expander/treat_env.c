/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:15 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:53:16 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*subenv(char *str)
{
	int		len;
	char	*env;

	len = 0;
	while (str[len] && ft_isenv(str[len]))
		len++;
	env = ft_substr(str, 0, len);
	return (env);
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

static char	*edit_line(char *line, char *env, int *i)
{
	char	*env_name;
	char	*env_value;
	char	*edited_line;

	env_name = subenv(env);
	env_value = getenv(env_name);
	free(env_name);
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

/* Treats the environment variable(s):
* - if the environment variable exists, replace it by its value.
* - else, deletes it from the line.
*/
char	*treat_env(char *line, bool prevent_eval)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isenv(line[i + 1]) || prevent_eval))
			line = edit_line(line, line + i + 1, &i);
		else if (line[i] == '$' && line[i + 1] && line[i + 1] == '?')
			line = edit_line_exit(line, ft_itoa(g_ms.exit_status), &i);
		else
			i++;
	}
	return (line);
}
