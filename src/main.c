#include "minishell.h"
#include "execution.h"
#include "parsing.h"
#include "error.h"

static void	init_global_struct(void)
{
	g_ms.l_token = NULL;
	g_ms.line = NULL;
	g_ms.node = NULL;
	g_ms.return_value = 0;
	g_ms.stdin_fileno = dup(STDIN_FILENO);
	g_ms.stdout_fileno = dup(STDOUT_FILENO);
}

static void	handle_line(char *line, char **envp)
{
	if (!*line)
		return ;
	add_history(line);
	g_ms.node = parsing(line);
	if (!g_ms.node)
	{
		free_tokens(&g_ms.l_token);
		free(line);
		exit(EXIT_FAILURE);
	}
	free_tokens(&g_ms.l_token);
	execute(g_ms.node, envp);
	free_tree(g_ms.node, false);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	(void)envp;
	init_global_struct();
	while ("apagnan")
	{
		g_ms.line = readline("minishell$ ");
		if (!g_ms.line)
			break ;
		handle_line(g_ms.line, envp);
		free(g_ms.line);
		// system("leaks minishell");
	}
	close(g_ms.stdin_fileno);
	close(g_ms.stdout_fileno);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
