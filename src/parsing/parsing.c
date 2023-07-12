#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>

// Note for self (Kian):
// The lexer is the first step of the parsing process
// the tokens are stored in a linked list of t_token
// the tokens are separated by their type
// the tokens are then passed to the parser
// the parser will check if the tokens are in the right order

/* UPDATE HANMIN:
* Our minishell does not treat the following case
* bash-3.2$ cat << EOF &&& echo haha
* bash-3.2$ bash: syntax error near unexpected token `&'
* bash-3.2$ EOF
*/

/* Parser part:
* Check the format of the line and creates binary tree(s) of command(s)
* for better execution flow in the execution part.
*/
static t_treenode	**parser(t_token *l_token)
{
	t_treenode	**cmdtable;

	cmdtable = NULL;
	if (!check_order(l_token) || !check_parentheses(l_token))
		return (NULL);
	cmdtable = get_cmdtable(l_token);
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
* - deals with redirections
* - creates the binary tree (or not if it is a simple command line)
*/
t_treenode	**parsing(void)
{
	t_treenode	**cmdtable;

	cmdtable = NULL;
	g_ms.l_token = lexer(g_ms.line);
	if (!g_ms.l_token)
		return (NULL);
	print_tokens(g_ms.l_token);
	cmdtable = parser(g_ms.l_token);
	if (!cmdtable)
		return (NULL);
	print_tree(cmdtable);
	return (cmdtable);
}
