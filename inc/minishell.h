#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "../libs/libft/inc/listft.h"
# include "../libs/libft/inc/charft.h"
# include "../libs/libft/inc/memft.h"
# include "../libs/libft/inc/isft.h"

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
	char	*line;
	int		cmp;
}	t_sep;

typedef struct	s_minishell
{
	char				*line;
	struct s_treenode	*node;
	struct s_cmdtable	*table;
}	t_minishell;

bool		parsing(t_minishell *ms);
t_cmdtable	*lexer(char *line);
char		*treat_env(char *cmd_line, int *i);
void		free_tokens(t_cmdtable **table);

#endif