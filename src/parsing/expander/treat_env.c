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
	char	*str;

	str = ft_substr(line, 0, start);
	tmp = ft_strjoin(str, replace);
	start++;
	while (line[start] && ft_isenv(line[start]))
		start++;
	free(str);
	str = ft_strjoin(tmp, line + start);
	free(tmp);
	return (str);
}

static char	*edit_line(char *line, int *i)
{
	char	*env;
	char	*tmp;
	char	*str;

	env = subenv(line + *i + 1);
	tmp = getenv(env);
	free(env);
	if (!tmp)
		str = replace_env(line, "", *i);
	else
	{
		str = replace_env(line, tmp, *i);
		*i += (int)ft_strlen(tmp) - 1;
	}
	free(line);
	return (str);
}

/* If the environment variable exists, replace it by its value.
* Else, deletes it from the command line.
*
* eg: $LIGNAME = "" ≠ $LOGNAMe = "" ≠ $LOGNAME = "hanmpark"
*/
char	*treat_env(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '$' && ft_isenv(line[i + 1])) || ft_ishome(line))
			line = edit_line(line, &i);
		else if (!ft_strncmp(line, "$?", 2))
		{
			free(line);
			line = ft_itoa(g_ms.return_value);
		}
		else
			i++;
	}
	return (line);
}
