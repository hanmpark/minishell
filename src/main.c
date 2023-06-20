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
	t_minishell	*ms;

	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	(void)envp;
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		return (1);
	ms->table = NULL;
	while ("apagnan")
	{
		ms->line = readline("minishell$ ");
		if (!ms->line)
			break ;
		if (*ms->line)
		{
			add_history(ms->line);
			parsing(ms); // parsing() is a boolean, it will be used when the execution part is completed
		}
		if (ms->table)
			free_tokens(&ms->table);
		free(ms->line);
		// system("leaks minishell");
	}
	return (EXIT_SUCCESS);
}
