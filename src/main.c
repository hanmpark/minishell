#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "error.h"

/*
* Once we have read the line from the prompt,...
* Ctrl + D = end the program as it returns (NULL).
*/

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	(void)envp;
	g_ms.l_token = NULL;
	g_ms.return_value = 0;
	g_ms.stdin_fileno = dup(STDIN_FILENO);
	g_ms.stdout_fileno = dup(STDOUT_FILENO);
	while ("apagnan")
	{
		g_ms.line = readline("minishell$ ");
		if (!g_ms.line)
			break ;
		if (*g_ms.line)
		{
			add_history(g_ms.line);
			g_ms.node = parsing(g_ms.line);
		}
		if (g_ms.l_token)
			free_tokens(&g_ms.l_token);
		if (g_ms.node)
		{
			execute(g_ms.node, envp);
			free_tree(g_ms.node);
		}
		free(g_ms.line);
		// system("leaks minishell");
	}
	printf("exit\n");
	return (EXIT_SUCCESS);
}
