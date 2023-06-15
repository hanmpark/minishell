#ifndef PARSING_H
# define PARSING_H

# define NBR_TYPES 11

typedef enum	e_type
{
	DLESS,
	DGREAT,
	OR_IF,
	AND_IF,
	LESS,
	GREAT,
	PIPE,
	LPAR,
	RPAR,
	QUOTE,
	DQUOTE,
	SPACE,
	WORD
}	t_type;

typedef struct	s_separator
{
	char	*cmpstr;
	int		bytes;
}	t_sep;

typedef struct	s_lexer
{
	t_cmdtable	*table;
	t_type		type;
	int			cur;
	int			last;
}	t_lex;

bool		parsing(t_minishell *ms);
t_cmdtable	*lexer(char *line);
void		tokenize(t_cmdtable **table, t_lex *lex, char *line);
bool		tokenize_quote(t_lex *lex, char *line);
t_type		is_separator(char *str);
void		skip_sep(t_cmdtable **table, t_lex *lex, char *line);

#endif