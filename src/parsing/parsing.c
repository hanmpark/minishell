#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>

// Prints out the tokens with their type (ONLY FOR DEBUG PURPOSE)
static void	print_tokens(t_token *l_token)
{
	int	count;

	count = 0;
	while (l_token)
	{
		printf("[%d] token = [%s] type = %d\n", count, l_token->token, l_token->type);
		l_token = l_token->next;
		count++;
	}
	printf("\n\n");
}

// Note for self (Kian):
// The lexer is the first step of the parsing process
// the tokens are stored in a linked list of t_token
// the tokens are separated by their type
// the tokens are then passed to the parser
// the parser will check if the tokens are in the right order

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
