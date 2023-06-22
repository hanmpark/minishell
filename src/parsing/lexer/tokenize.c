#include "minishell.h"
#include "parsing.h"
#include "error.h"

static int	nbr_skip(char *str, t_type type)
{
	int	skip;

	if (!str)
		return (0);
	skip = 0;
	while (str[skip] && ft_isspace(str[skip]))
		skip++;
	if (type == DLESS || type == DGREAT || type == OR_IF || type == AND_IF)
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
* - if ≠ spaces, tokenizes the sep
* - else, skip spaces and go to the next token
*/
static void	skip_sep(t_cmdtable **table, t_lex *lex, char *line)
{
	int	skip;

	skip = nbr_skip(line + lex->cur, lex->type);
	if (lex->type != SPACE && line[lex->cur])
		ft_lstadd_back(table, ft_lstnew(ft_substr(line, lex->cur, skip), \
			lex->type));
	if (!skip && line[lex->cur])
		lex->cur++;
	lex->cur += skip;
	lex->last = lex->cur;
}

/* Creates tokens and their type:
* - they are stored in linked lists
* - creates a token which stores everything between quotes without expanding
* variables
* - returns false if the second quotation mark is not found
*/
bool	tokenize(t_cmdtable **table, t_lex *lex, char *line)
{
	char	*token;

	token = ft_substr(line, lex->last, lex->cur - lex->last);
	if (lex->type == QUOTE || lex->type == DQUOTE)
		token = tokenize_string(lex, token, line);
	if (!token)
		return (false);
	if (*token)
		ft_lstadd_back(table, ft_lstnew(token, WORD));
	else if (!*token)
		free(token);
	skip_sep(table, lex, line);
	return (true);
}
