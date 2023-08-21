/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:26:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/21 09:56:12 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "signals.h"
#include "putft.h"
#include "exit.h"

/*
* Handles the given line in 3 parts:
* 1. parses the line: tokenizes and processes the input line
* through lexing, parsing, and expanding stages.
* 2. creates an AST: stores the relevant data in an Abstract Syntax Tree (AST)
* to represent the parsed line's structure.
* 3. executes the line: if parsing is successful,
* executes the actions specified by the AST.
*/
static void	handle_line(t_mnsh *mnsh)
{
	t_tree	*tree;

	if (!*mnsh->line)
	{
		free(mnsh->line);
		return ;
	}
	add_history(mnsh->line);
	tree = parsing(mnsh);
	free(mnsh->line);
	if (!tree)
		return ;
	execute(mnsh, tree);
	free_tree(tree);
}

static void	handle_loop(t_mnsh *mnsh)
{
	char	*prompt;

	while ("apagnan")
	{
		setup_basic_signals_handlers();
		set_termios(true);
		prompt = get_prompt(getcwd(NULL, 0));
		mnsh->line = readline(prompt);
		free(prompt);
		set_termios(false);
		if (!mnsh->line)
		{
			ft_putstr_fd(UP, STDOUT_FILENO);
			ft_putstr_fd(rl_prompt, STDOUT_FILENO);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		handle_line(mnsh);
	}
}

/*
* Minishell's main:
* A command-line interpreter that can execute
* basic shell commands and provide a shell-like environment.
*
* To see how the tokens are created and see the AST:
* ./minishell debug
*/
int	main(int argc, char **argv, char **envp)
{
	t_mnsh	*mnsh;

	mnsh = init_mnsh(argc, argv, envp);
	if (!mnsh)
		return (EXIT_FAILURE);
	handle_loop(mnsh);
	ft_arrayfree(mnsh->envp);
	free(mnsh);
	return (EXIT_SUCCESS);
}
