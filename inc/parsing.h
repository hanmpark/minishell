#ifndef PARSING_H
# define PARSING_H

# define READ 0
# define TRUNC 1
# define APPEND 2

typedef struct	s_separator
{
	char	*cmpstr;
	int		bytes;
}	t_sep;

typedef struct	s_lexer
{
	t_token		*l_token;
	t_type		type;
	int			cur;
	int			last;
}	t_lex;

t_treenode	**parsing(void);

t_token		*lexer(char *line);
bool		tokenize(t_token **l_token, t_lex *lex, char *line);
char		*tokenize_string(t_lex *lex, char *str, char *line);

t_type		is_separator(char *str);
int			is_undefined(char *str);
bool		is_redir(t_type type);
bool		is_cmdsep(t_type type);
bool		is_par(t_type type);

t_treenode	**parser(t_token *l_token);
bool		check_order(t_token *l_token);
bool		check_parentheses(t_token *l_token);
t_treenode	**get_cmdtable(t_token *l_token);
t_cmd		*get_cmd(t_token *l_token);
bool		treat_redir(t_cmd *cmd, t_token *l_token, t_type type);
int			here_doc(char *limiter);

t_token		*next_cmd(t_token *l_token);
t_token		*next_pipeline(t_token *l_token);
t_token		*next_token(t_token *l_token);

#endif