#include "minishell.h"

/*
* Once we have read the line from the prompt,...
* Ctrl + D = end the program as it returns (NULL).
*/

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*ms;

	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	(void)envp;
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		return (1);
	while ("apagnan")
	{
		ms->line = readline("minishell$ ");
		if (!ms->line)
			break ;
		if (*ms->line)
			add_history(ms->line);
		if(!parsing(ms))
		{
			free(ms->line);
			break ;
		}
		free(ms->line);
	}
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}
