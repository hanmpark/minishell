/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:27 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/09 15:00:02 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
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

# define FIRST_COLOR "\033[38;5;183m"
# define LAST_COLOR "\033[38;5;191m"
# define DEF "\033[0m"

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

int		g_exit;

t_mnsh	*init_mnsh(int argc, char **argv, char **envp);
void	set_termios(bool set);
char	*get_prompt(char *cwd);
void	handle_signal(void);
void	interaction_mod(void);

/* FOR DEBUGGING PURPOSE */

void	print_tree(t_tree *node);
void	print_tokens(t_tok *l_token);

#endif