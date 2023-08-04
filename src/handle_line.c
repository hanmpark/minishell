/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:31 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/04 16:01:04 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "exit.h"

#include <stdbool.h>

/* Parser part:
* Check the format of the line and creates binary tree(s) of command(s)
* for better execution flow in the execution part.
*/
static t_treenode	*parser(t_token *l_token)
{
	t_treenode	*cmdtable;

	cmdtable = NULL;
	if (!check_order(l_token) || !check_parentheses(l_token))
		return (NULL);
	cmdtable = get_table(l_token);
	if (!cmdtable)
		return (NULL);
	return (cmdtable);
}

/* Lexer part:
* Divides the given line into sequence of tokens
* This will help the program identify the building blocks of the command(s)
* If no error has been encountered, returns the command table (t_token *).
*/
static t_token	*lexer(char *line)
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

/* Parses the given line:
* - creates tokens
* - checks the order of the token (parentheses, redirection, etc.)
* - deals with redirections and stores it in the command structure (t_cmd)
* - creates the binary tree
*/
static t_treenode	*parsing(char *line, bool is_debug)
{
	t_treenode	*cmdtable;
	t_token		*l_token;

	cmdtable = NULL;
	l_token = lexer(line);
	if (!l_token)
		return (NULL);
	cmdtable = parser(l_token);
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

/* Handles the given line:
* - parse the line first (lexer, parser, expander)
* - stores all the important data to an AST (t_treenode)
* - if everything is parsed, execute the line
*/
void	handle_line(char *line, char ***envp, bool is_debug)
{
	t_treenode	*tree;

	if (!*line)
		return ;
	add_history(line);
	tree = parsing(line, is_debug);
	free(line);
	if (!tree)
		return ;
	execute(tree, envp);
	free_tree(tree);
}
