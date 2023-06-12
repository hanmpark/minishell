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

typedef enum	e_type
{
	WORD,
	PIPE,
	LPAR,
	RPAR,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	OR_IF,
	AND_IF
}	t_type;

typedef struct	s_minishell
{
	char				*line;
	struct s_treenode	*node;
}	t_minishell;

bool	parsing(t_minishell *ms);
char	*treat_env(char *cmd_line, int *i);

#endif