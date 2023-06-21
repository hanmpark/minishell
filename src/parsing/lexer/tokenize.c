#include "minishell.h"
#include "parsing.h"

static int	nbr_skip(char *str, t_type type)
{
	int	skip;

	if (!str)
		return (0);
	skip = 0;
	while (str[skip] && ft_isspace(str[skip]))
		skip++;
	if (type == DLESS || type == DGREAT || type == OR_IF || type == AND_IF || \
		(type == LESS && *(str + 1) == '>'))
		return (2);
	else if (type == UNDEFINED && is_undefined(str))
		return (is_undefined(str));
	else if ((type == UNDEFINED && *str == '&'))
		return (1);
	else if (type != WORD && !ft_isspace(*str))
		return (1);
	return (skip);
}

/* Skips the separator:
* - if it is different from spaces, tokenizes it
* - else, it ignores and continue tokenizing the left characters in the line
*/
void	skip_sep(t_cmdtable **table, t_lex *lex, char *line)
{
	int	skip;

	skip = nbr_skip(line + lex->cur, lex->type);
	printf("skip = %d\nline[lex->cur] = %c\n", skip, line[lex->cur]);
	if (lex->type != SPACE && line[lex->cur])
		ft_lstadd_back(table, ft_lstnew(ft_substr(line, lex->cur, skip), \
			lex->type));
	if (lex->type == DLESS)
		lex->here_doc = true;
	if (!skip && line[lex->cur])
		lex->cur++;
	lex->cur += skip;
	lex->last = lex->cur;
}

void	tokenize(t_cmdtable **table, t_lex *lex, char *line)
{
	char	*token;

	token = ft_substr(line, lex->last, lex->cur - lex->last);
	if (!lex->here_doc)
		token = treat_env(token);
	if (*token)
	{
		ft_lstadd_back(table, ft_lstnew(token, WORD));
		lex->here_doc = false;
	}
	else if (!*token)
		free(token);
	skip_sep(table, lex, line);
}
