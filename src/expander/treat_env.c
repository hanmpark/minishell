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

static char	*replace_env(char *line, char *replace, int start)
{
	char	*tmp;
	char	*edited_line;

	edited_line = ft_substr(line, 0, start);
	tmp = ft_strjoin(edited_line, replace);
	free(edited_line);
	start++;
	while (line[start] && ft_isenv(line[start]))
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
		edited_line = replace_env(line, "", *i);
	else
	{
		edited_line = replace_env(line, env_value, *i);
		*i += (int)ft_strlen(env_value) - 1;
	}
	free(line);
	return (edited_line);
}

/* If the environment variable exists, replace it by its value.
* Else, deletes it from the line.
*/
char	*treat_env(char *line, bool prevent_eval)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isenv(line[i + 1]) || prevent_eval))
			line = edit_line(line, line + i + 1, &i);
		else if (ft_ishome(line))
			line = edit_line(line, "HOME", &i);
		else if (!ft_strncmp(line, "$?", 2))
		{
			free(line);
			line = ft_itoa(g_ms.exit_status);
		}
		else
			i++;
	}
	return (line);
}
