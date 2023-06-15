#include "minishell.h"
#include "parsing.h"

t_type	is_separator(char *str)
{
	static t_sep	sep[] = {{"<<", 2}, {">>", 2}, {"||", 2}, {"&&", 2}, \
		{"<", 1}, {">", 1}, {"|", 1}, {"(", 1}, {")", 1}, {"\'", 1}, \
		{"\"", 1}};
	int				i;

	i = -1;
	while (++i < NBR_TYPES)
		if (!ft_strncmp(str, sep[i].cmpstr, sep[i].bytes))
			return (i);
	if (ft_isspace(*str))
		return (SPACE);
	else
		return (WORD);
}

static int	nbr_skip(char *str)
{
	int	skip;

	if (!str)
		return (0);
	skip = 0;
	while (str[skip] && ft_isspace(str[skip]))
		skip++;
	if (is_separator(str) == DLESS || is_separator(str) == DGREAT || \
		is_separator(str) == OR_IF || is_separator(str) == AND_IF)
		return (2);
	else if (is_separator(str) != WORD && !ft_isspace(*str))
		return (1);
	else
		return (skip);
}

/* Skips the separator:
* - if it is different from spaces, tokenizes it
* - else, it ignores and continue tokenizing the left characters in the line
*/
void	skip_sep(t_cmdtable **table, t_lex *lex, char *line)
{
	int	skip;

	skip = nbr_skip(line + lex->cur);
	if (lex->type != SPACE && line[lex->cur])
		ft_lstadd_back(table, ft_lstnew(ft_substr(line, lex->cur, skip), \
			lex->type));
	if (!skip && line[lex->cur])
		lex->cur++;
	lex->cur += skip;
	lex->last = lex->cur;
}

void	tokenize(t_cmdtable **table, t_lex *lex, char *line)
{
	char	*token;

	token = treat_env(ft_substr(line, lex->last, lex->cur - lex->last));
	if (*token)
		ft_lstadd_back(table, ft_lstnew(token, WORD));
	else if (!*token)
		free(token);
	skip_sep(table, lex, line);
}
