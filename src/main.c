#include "minishell.h"

/*
* Once we have read the line from the prompt,...
* Ctrl + D = end the program as it returns (NULL).
*/

int	main(void)
{
	t_data	*ms;

	ms = malloc(sizeof(t_data));
	if (!ms)
		return (1);
	while ("apagnan")
	{
		ms->line = readline("minishell$ ");
		if (!ms->line)
			break ;
		add_history(ms->line);
		parsing(ms);
		free(ms->line);
	}
	// system("leaks minishell");
	return (0);
}
