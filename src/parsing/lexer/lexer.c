#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>

/* Separate tokens:
* - reads each character and tokenize them by their type
* - the line is split with the separators
*/
static bool	separate_token(t_lex *lex, char *line)
{
	lex->type = is_separator(line + lex->cur);
	if (lex->type != WORD || !line[lex->cur])
	{
		if (!tokenize(&lex->table, lex, line))
			return (false);
	}
	else
		lex->cur++;
	return (true);
}

/* Divides the given line into sequence of tokens
* This will help the program identify the building blocks of the command(s)
* If no error has been encountered, returns the command table (t_cmdtable *)
*/
t_cmdtable	*lexer(char *line)
{
	t_lex	lex;

	lex.cur = 0;
	lex.last = 0;
	lex.redir = false;
	lex.table = NULL;
	while (line[lex.last])
	{
		if (!separate_token(&lex, line))
		{
			free_tokens(&lex.table);
			return (NULL);
		}
	}
	return (lex.table);
}
