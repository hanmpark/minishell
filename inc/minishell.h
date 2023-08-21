/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:27 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/21 10:06:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "structft.h"
# include "charft.h"
# include "memft.h"

# define NBR_TYPES 11
# define NBR_UDF 10

/* PROMPT */

# define TITLE_COLOR "\001\033[1;38;5;198m\002"
# define PROMPT_COLOR "\001\033[1;38;5;75m\002"
# define SUCCESS_COLOR "\001\033[1;38;5;83m\002"
# define ERROR_COLOR "\001\033[1;38;5;196m\002"
# define DEF "\001\033[0m\002"
# define UP "\001\033[1A\002"

/* TYPEDEF */

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
	WHITE_SPACE,
	WORD
}	t_type;

typedef struct s_minishell
{
	char	*line;
	char	**envp;
	bool	is_debug;
}	t_mnsh;

/* GLOBAL VARIABLE */

int	g_sig;

/* INITIALIZATION */

t_mnsh	*init_mnsh(int argc, char **argv, char **envp);
char	*get_prompt(char *cwd);

/* FOR DEBUGGING PURPOSE */

void	print_tree(t_tree *node);
void	print_tokens(t_tok *l_token);

#endif