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

static char	*edit_line(char *cmd_line, int *i)
{
	char	*env;
	char	*tmp;
	char	*line;

	env = subenv(cmd_line + *i + 1);
	tmp = getenv(env);
	free(env);
	if (!tmp)
		line = replace_env(cmd_line, "", *i);
	else
	{
		line = replace_env(cmd_line, tmp, *i);
		*i += (int)ft_strlen(tmp) - 1;
	}
	free(cmd_line);
	return (line);
}

/* If the environment variable exists, replace it by its value.
* Else, deletes it from the command line.
*
* eg: $LIGNAME = "" ≠ $LOGNAMe = "" ≠ $LOGNAME = "hanmpark"
*/
char	*treat_env(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '$' && ft_isenv(cmd_line[i + 1]))
			cmd_line = edit_line(cmd_line, &i);
		else
			i++;
	}
	return (cmd_line);
}
