#include "minishell.h"
#include "parsing.h"

// void	exec_line(t_minishell *ms)
// {
// 	builtin_cmds(ms);
// }

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
	while ("apagnan")
	{
		g_ms.line = readline("minishell$ ");
		if (!g_ms.line)
			break ;
		if (*g_ms.line)
		{
			add_history(g_ms.line);
			g_ms.node = parsing(); // parsing() is a boolean, it will be used when the execution part is completed
		}
		if (g_ms.l_token)
			free_tokens(&g_ms.l_token);
		free(g_ms.line);
		// system("leaks minishell");
	}
	return (EXIT_SUCCESS);
}
