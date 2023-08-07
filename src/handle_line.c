/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:31 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/07 14:05:38 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "exit.h"

#include <stdbool.h>

/*
* Parser part:
* - verifies the format of the line and creates a binary tree of commands.
* - this step ensures a well-structured execution flow
* during the execution phase.
*/
static t_tree	*parser(t_tok *l_token, char **envp)
{
	t_tree	*cmdtable;

	cmdtable = NULL;
	if (!check_order(l_token) || !check_parentheses(l_token))
		return (NULL);
	cmdtable = get_table(l_token, envp);
	if (!cmdtable)
		return (NULL);
	return (cmdtable);
}

/*
* Lexer part:
* - divides the given line into a sequence of tokens.
* - identifies the building blocks of the command(s) using these tokens.
* - if no errors are encountered, returns the command table.
*/
static t_tok	*lexer(char *line)
{
	t_lex	lex;

	lex.cur = 0;
	lex.last = 0;
	lex.l_token = NULL;
	while (line[lex.last])
	{
		if (!tokenize(&lex, line))
		{
			free_tokens(&lex.l_token);
			return (NULL);
		}
	}
	return (lex.l_token);
}

/*
* Parsing part:
* - parses the line: creates tokens from the input line and checks
* the order of tokens to handle special cases like
* parentheses and redirections.
* - generates the minishell's AST to represent the parsend line's structure.
*/
static t_tree	*parsing(char *line, bool is_debug, char **envp)
{
	t_tree	*cmdtable;
	t_tok	*l_token;

	cmdtable = NULL;
	l_token = lexer(line);
	if (!l_token)
		return (NULL);
	cmdtable = parser(l_token, envp);
	if (!cmdtable)
	{
		free_tokens(&l_token);
		return (NULL);
	}
	if (is_debug)
	{
		print_tokens(l_token);
		print_tree(cmdtable);
	}
	free_tokens(&l_token);
	return (cmdtable);
}

/*
* Handles the given line in 3 parts:
* 1. parses the line: tokenizes and processes the input line
* through lexing, parsing, and expanding stages.
* 2. creates an AST: stores the relevant data in an Abstract Syntax Tree (AST)
* to represent the parsed line's structure.
* 3. executes the line: if parsing is successful,
* executes the actions specified by the AST.
*/
void	handle_line(char *line, char ***envp, bool is_debug)
{
	t_tree	*tree;

	if (!*line)
		return ;
	add_history(line);
	tree = parsing(line, is_debug, *envp);
	free(line);
	if (!tree)
		return ;
	execute(tree, envp);
	free_tree(tree);
}
