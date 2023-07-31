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
	struct s_treenode	*node;
	struct s_token		*l_token;
	int					stdin_fileno;
	int					stdout_fileno;
	int					exit_status;
	bool				is_debug;
}	t_minishell;

struct s_minishell	g_ms;

void	set_termios(bool set);

// only for debugging purpose
void	print_tree(t_treenode *node);
void	print_tokens(t_token *l_token);

#endif