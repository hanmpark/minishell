#include "minishell.h"

/*
* Once we have read the line from the prompt,...
* Ctrl + D = end the program as it returns (NULL).
*/

int	main(int argc, char **argv, char **envp)
{
	t_data	*ms;

	if (argc != 1)
		return (EXIT_FAILURE);
	ms = malloc(sizeof(t_data));
	if (!ms)
		return (1);
	while ("apagnan")
	{
		ms->line = readline("minishell$ ");
		if (!ms->line)
			break ;
		if (*ms->line)
			add_history(ms->line);
		parsing(ms);
		free(ms->line);
	}
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}
