#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

/* Have to treat the following case:
* bash$ export MYVAR="hello world"
* bash$ <$MYVAR
* bash: $MYVAR: ambiguous redirect
* bash$ <"$MYVAR"
* bash: hello world: No such file or directory
*
* This is why I'm going to do the variable expansions after the parser
*/

static char	*quote_str(char *line, int *cur)
{
	char	quote_type;
	int		start;
	char	*str;

	quote_type = line[*cur];
	start = ++*cur;
	while (line[*cur] != quote_type)
		*cur++;
	str = ft_substr(line, start, *cur - start);
	if (quote_type == '"')
		str = treat_env(str);
	++*cur;
	return (str);
}

static char	*word_str(char *line, int *cur)
{
	char	*str;
	int		start;

	start = *cur;
	while (line[*cur] && (line[*cur] != '\'' && line[*cur] != '"'))
		*cur++;
	str = ft_treatenv(ft_substr(line, start, *cur - start));
	return (str);
}

static char	*join_token(char *join, char *line, int *cur)
{
	char	*str;
	char	*add_token;

	if (line[*cur] == '\'' || line[*cur] == '"')
		str = quote_str(line, cur);
	else
		str = word_str(line, cur);
	add_token = ft_strjoin(join, str);
	free(join);
	free(str);
	return (add_token);
}

char	*expand_token(char *line)
{
	char	*str;
	int		cur;

	cur = 0;
	while (line[cur] && (line[cur] != '\'' || line[cur] != '"'))
		cur++;
	str = ft_substr(line, 0, cur);
	while (line[cur])
		str = join_token(str, line, &cur);
	free(line);
	return (str);
}

char	**expander_cmd(char *line)
{
	char	**cmd;
	int		cur;

	cur = 0;
	while (line[cur] && (line[cur] != '\'' || line[cur] != '"'))
		cur++;
	*cmd = ft_substr(line, 0, cur);
	while (line[cur])
		str = join_token(str, line, &cur);
	free(line);
	return (newline);
}