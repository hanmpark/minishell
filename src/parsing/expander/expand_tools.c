#include "minishell.h"
#include "expander.h"

char	*get_quotestr(char *line, int *cur)
{
	char	quote_type;
	int		start;
	char	*str;

	quote_type = line[*cur];
	start = ++(*cur);
	while (line[*cur] != quote_type)
		(*cur)++;
	str = ft_substr(line, start, *cur - start);
	if (quote_type == '"')
		str = treat_env(str);
	++(*cur);
	return (str);
}

char	*word_str(char *line, int *cur)
{
	char	*str;
	int		start;

	start = *cur;
	while (line[*cur] && (line[*cur] != '\'' && line[*cur] != '"'))
		(*cur)++;
	str = treat_env(ft_substr(line, start, *cur - start));
	return (str);
}
