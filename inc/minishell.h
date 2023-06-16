#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "../lib/libft/inc/listft.h"
# include "../lib/libft/inc/charft.h"
# include "../lib/libft/inc/memft.h"
# include "../lib/libft/inc/isft.h"
# include "../lib/libft/inc/putft.h"

typedef struct	s_minishell
{
	char				*line;
	struct s_treenode	*node;
	struct s_cmdtable	*table;
}	t_minishell;

char	*treat_env(char *cmd_line);
void	free_tokens(t_cmdtable **table);

#endif