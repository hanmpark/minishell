#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "../lib/libft/inc/ft_printf.h"
# include "../lib/libft/inc/structft.h"
# include "../lib/libft/inc/charft.h"
# include "../lib/libft/inc/memft.h"
# include "../lib/libft/inc/isft.h"
# include "../lib/libft/inc/putft.h"

# define NBR_TYPES 11
# define NBR_UDF 10

typedef enum e_type
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
	UNDEFINED,
	SPACE,
	WORD
}	t_type;

typedef struct s_minishell
{
	char				*line;
	bool				is_debug;
	char				**envp;
}	t_minishell;

int		g_exit;

t_minishell	*init_minishell(int argc, char **argv, char **envp);
void		set_termios(bool set);

/* FOR DEBUGGING PURPOSE */

void		print_tree(t_tree *node);
void		print_tokens(t_tok *l_token);

#endif