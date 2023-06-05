#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "../libs/libft/inc/listft.h"
# include "../libs/libft/inc/charft.h"

typedef enum	s_quote
{
	NONE,
	NOT_CLOSED,
	CLOSED
}	t_quote;

#endif