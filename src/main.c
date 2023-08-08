#include "minishell.h"
#include "parsing.h"

/*
* Minishell's main:
* A command-line interpreter that can execute
* basic shell commands and provide a shell-like environment.
*
* To see how the tokens are created and see the AST:
* ./minishell debug
*/
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mnsh;
	char		*prompt;

	mnsh = init_minishell(argc, argv, envp);
	if (!mnsh)
		return (EXIT_FAILURE);
	while ("apagnan")
	{
		prompt = get_prompt(getcwd(NULL, 0));
		mnsh->line = readline(prompt);
		free(prompt);
		if (!mnsh->line)
			break ;
		handle_line(mnsh->line, &mnsh->envp, mnsh->is_debug);
		// system("leaks minishell");
	}
	ft_arrayfree(mnsh->envp);
	free(mnsh);
	write(1, "exit\n", 5);
	set_termios(false);
	return (EXIT_SUCCESS);
}
