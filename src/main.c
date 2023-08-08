#include "minishell.h"
#include "parsing.h"

static void	handle_loop(t_mnsh *mnsh)
{
	char	*prompt;

	while ("apagnan")
	{
		prompt = get_prompt(getcwd(NULL, 0));
		mnsh->line = readline(prompt);
		free(prompt);
		if (!mnsh->line)
			break ;
		handle_line(mnsh);
		// system("leaks minishell");
	}
}

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
	t_mnsh	*mnsh;

	mnsh = init_mnsh(argc, argv, envp);
	if (!mnsh)
		return (EXIT_FAILURE);
	handle_loop(mnsh);
	set_termios(false);
	ft_arrayfree(mnsh->envp);
	free(mnsh);
	write(1, "exit\n", 5);
	return (EXIT_SUCCESS);
}
