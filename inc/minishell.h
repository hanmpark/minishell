/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:27 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:48:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	SPACE,
	WORD
}	t_type;

typedef struct s_minishell
{
	char	*line;
	char	**envp;
	bool	is_debug;
	int		exit;
}	t_mnsh;

t_mnsh	*init_mnsh(int argc, char **argv, char **envp);
void	set_termios(bool set);
char	*get_prompt(char *cwd);

/* FOR DEBUGGING PURPOSE */

void	print_tree(t_tree *node);
void	print_tokens(t_tok *l_token);

#endif