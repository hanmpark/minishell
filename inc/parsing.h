#ifndef PARSING_H
# define PARSING_H

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
	bool		here_doc;
}	t_lex;

bool		parsing(t_minishell *ms);

t_cmdtable	*lexer(char *line);
void		tokenize(t_cmdtable **table, t_lex *lex, char *line);
bool		tokenize_quote(t_lex *lex, char *line);
void		skip_sep(t_cmdtable **table, t_lex *lex, char *line);

t_type		is_separator(char *str);
int			is_undefined(char *str);
bool		is_redir(t_type type);
bool		is_cmdsep(t_type type);

bool		parser(t_cmdtable *table);

#endif