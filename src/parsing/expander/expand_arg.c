#include "minishell.h"
#include "expander.h"

/* Have to treat the following case:
* bash$ export MYVAR="hello world"
* bash$ <$MYVAR
* bash: $MYVAR: ambiguous redirect
* bash$ <"$MYVAR"
* bash: hello world: No such file or directory
*
* This is why I'm going to do the variable expansions after the parser
*/

static char	*join_quotes(char *join, char *line, int *cur)
{
	char	*str;
	char	*add_token;

	if (line[*cur] == '\'' || line[*cur] == '"')
		str = get_quotestr(line, cur);
	else
		str = word_str(line, cur);
	add_token = ft_strjoin(join, str);
	free(join);
	free(str);
	return (add_token);
}

char	*expand_arg(char *line)
{
	char	*str;
	int		cur;

	cur = 0;
	while (line[cur] && (line[cur] != '\'' && line[cur] != '"'))
		cur++;
	str = treat_env(ft_substr(line, 0, cur));
	if (!line[cur] && !*str)
	{
		free(str);
		free(line);
		return (NULL);
	}
	while (line[cur])
		str = join_quotes(str, line, &cur);
	free(line);
	return (str);
}
