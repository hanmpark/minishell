/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:27 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 14:41:29 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_printf.h"
# include "structft.h"
# include "charft.h"
# include "memft.h"
# include "isft.h"
# include "putft.h"

# define NBR_TYPES 11
# define NBR_UDF 10

/* PROMPT */

# define FIRST_COLOR "\001\033[38;5;183m\002"
# define LAST_COLOR "\001\033[38;5;191m\002"
# define DEF "\001\033[0m\002"
# define UP "\001\033[1A\002"

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
	struct sigaction	*sa;
	char				*line;
	char				**envp;
	bool				is_debug;
}	t_mnsh;

/* GLOBAL VARIABLE */

int		g_exit;

t_mnsh	*init_mnsh(int argc, char **argv, char **envp);
char	*get_prompt(char *cwd);

/* FOR DEBUGGING PURPOSE */

void	print_tree(t_tree *node);
void	print_tokens(t_tok *l_token);

#endif