#ifndef PARSING_H
# define PARSING_H

# define READ 0
# define TRUNC 1
# define APPEND 2

typedef struct s_separator
{
	char	*cmpstr;
	int		bytes;
}	t_sep;

typedef struct s_lexer
{
	t_tok		*l_token;
	t_type		type;
	int			cur;
	int			last;
}	t_lex;

void	handle_line(char *line, char ***envp, bool is_debug);

bool	tokenize(t_lex *lex, char *line);
char	*tokenize_string(t_lex *lex, char *str, char *line);

t_type	is_separator(char *str);
int		is_undefined(char *str);
bool	is_redir(t_type type);
bool	is_cmdsep(t_type type);
bool	is_par(t_type type);

bool	check_order(t_tok *l_token);
bool	check_parentheses(t_tok *l_token);
bool	check_filename(t_tok *token, char **envp);

t_tree	*get_table(t_tok *l_token, char **envp);
t_cmd	**get_simple_cmd(t_tok **l_tok, t_tree *node, char **envp);
bool	handle_redirection(t_cmd *cmd, t_tok **l_token, char **envp);
int		here_doc(char *token, char **envp);
char	*format_limiter(char *token);

#endif