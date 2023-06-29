#include "minishell.h"
#include "expander.h"

char	*quote_str(char *line, int *cur)
{
	char	quote_type;
	int		start;
	char	*str;

	quote_type = line[*cur];
	start = ++*cur;
	while (line[*cur] != quote_type)
		*cur = *cur + 1;
	str = ft_substr(line, start, *cur - start);
	if (quote_type == '"')
		str = treat_env(str);
	++*cur;
	return (str);
}

char	*word_str(char *line, int *cur)
{
	char	*str;
	int		start;

	start = *cur;
	while (line[*cur] && (line[*cur] != '\'' && line[*cur] != '"'))
		*cur = *cur + 1;
	str = treat_env(ft_substr(line, start, *cur - start));
	return (str);
}
