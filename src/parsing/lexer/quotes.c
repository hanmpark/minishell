#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>

static char	*quote_str(t_lex *lex, char *line)
{
	char	quote_type;
	char	*str;

	quote_type = line[lex->cur];
	lex->last = ++lex->cur;
	while (line[lex->cur] && line[lex->cur] != quote_type)
		lex->cur++;
	if (!line[lex->cur])
		return (NULL);
	str = ft_substr(line, lex->last, lex->cur - lex->last);
	lex->last = ++lex->cur;
	return (str);
}

static char	*word_str(t_lex *lex, char *line)
{
	char	*str;

	while (line[lex->cur] && is_separator(line + lex->cur) == WORD)
		lex->cur++;
	str = ft_substr(line, lex->last, lex->cur - lex->last);
	lex->last = lex->cur;
	return (str);
}

static char	*put_to_token(t_lex *lex, char *join, char *line)
{
	char	*str;
	char	*add_token;

	if (lex->type == QUOTE || lex->type == DQUOTE)
	{
		str = quote_str(lex, line);
		if (!str)
		{
			free(join);
			return (NULL);
		}
	}
	else
		str = word_str(lex, line);
	add_token = ft_strjoin(join, str);
	free(join);
	free(str);
	return (add_token);
}

static char	*single_token(t_lex *lex, char *final_token, char *line)
{
	while (line[lex->cur] && (lex->type == QUOTE || lex->type == DQUOTE || \
		lex->type == WORD))
	{
		final_token = put_to_token(lex, final_token, line);
		if (!final_token)
			return (NULL);
		if ((lex->type == QUOTE || lex->type == WORD) && !lex->here_doc)
			final_token = treat_env(final_token);
		lex->type = is_separator(line + lex->cur);
	}
	return (final_token);
}

/* Tokenizes quote cases:
* - if no separator is found, everything is put into one token
* - if a '$' is found inside a simple quote string, does not replace it
* by its value
* - else, replace it by its value
*/
bool	tokenize_quote(t_lex *lex, char *line)
{
	char	*str;

	if (lex->last < lex->cur)
	{
		str = ft_substr(line, lex->last, lex->cur - lex->last);
		if (!lex->here_doc)
			str = treat_env(str);
		lex->last = lex->cur;
	}
	else
		str = ft_strdup("");
	str = single_token(lex, str, line);
	if (!str)
		return (error_quote(lex->type));
	ft_lstadd_back(&lex->table, ft_lstnew(str, WORD));
	lex->here_doc = false;
	skip_sep(&lex->table, lex, line);
	return (true);
}
