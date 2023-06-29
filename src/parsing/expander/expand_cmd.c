#include "minishell.h"
#include "expander.h"

static char	**join_quote(char **join, char *line, int *cur)
{
	char	*str;
	char	*last_element;
	int		len;

	len = ft_arraylen(join);
	if (len > 0)
		len--;
	str = quote_str(line, cur);
	if (!join[len])
		last_element = ft_strdup("");
	else
		last_element = ft_strdup(join[len]);
	free(join[len]);
	join[len] = ft_strjoin(last_element, str);
	free(last_element);
	free(str);
	return (join);
}

static char	**join_args(char **join, char *line, int *cur)
{
	char	**new_ar;
	char	*tmp;

	tmp = NULL;
	if (line[*cur] == '\'' || line[*cur] == '"')
		new_ar = join_quote(join, line, cur);
	else
	{
		tmp = word_str(line, cur);
		new_ar = ft_arrayjoin(join, ft_split(tmp, ' '));
		free(tmp);
	}
	return (new_ar);
}

char	**expand_cmd(char *line)
{
	char	**cmd;
	char	*last_element;
	int		cur;

	cur = 0;
	while (line[cur] && (line[cur] != '\'' && line[cur] != '"'))
		cur++;
	last_element = treat_env(ft_substr(line, 0, cur));
	if (!line[cur] && !*last_element)
	{
		free(last_element);
		free(line);
		return (NULL);
	}
	cmd = ft_split(last_element, ' ');
	free(last_element);
	while (line[cur])
		cmd = join_args(cmd, line, &cur);
	free(line);
	return (cmd);
}
