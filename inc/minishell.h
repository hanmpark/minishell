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

typedef enum	s_token
{
	WORD,
	OPERATORS,
	REDIRECTIONS
} t_token;

// typedef enum	s_operators
// {
// 	AND_IF = 3,
// 	OR_IF,
// 	PIPE,
// 	LESS,
// 	GREAT,
// 	DLESS,
// 	DGREAT,
// 	LPAR,
// 	RPAR
// } t_operators;

typedef struct	s_data
{
	char	*line;
	char	**token;
	int		nb_cmd;
}	t_data;

bool	parsing(t_data *ms);
char	*treat_env(char *cmd_line, int *i);

#endif