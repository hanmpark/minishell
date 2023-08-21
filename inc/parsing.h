/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:29 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/21 10:08:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define READ 0
# define TRUNC 1
# define APPEND 2

# define HERE_DOC_SIG -2

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

t_tree	*parsing(t_mnsh *mnsh);

/* LEXER */

bool	tokenize(t_lex *lex, t_mnsh *mnsh);
char	*tokenize_string(t_lex *lex, t_mnsh *mnsh, char *token);

/* FIND TYPE */

t_type	is_separator(char *str);
int		is_undefined(char *str);
bool	is_redir(t_type type);
bool	is_cmdsep(t_type type);
bool	is_par(t_type type);

/* CHECKER */

bool	check_order(t_tok *l_token);
bool	check_parentheses(t_tok *l_token);
bool	check_filename(t_mnsh *mnsh, t_tok *token);

/* PARSER */

t_tree	*get_table(t_tok *l_token, t_mnsh *mnsh);
t_cmd	**get_simple_cmd(t_mnsh *mnsh, t_tok **l_tok, t_tree *node);
bool	handle_redirection(t_mnsh *mnsh, t_cmd *cmd, t_tok **l_token);
int		here_doc(t_mnsh *mnsh, char *token);
char	*format_limiter(char *token);

#endif