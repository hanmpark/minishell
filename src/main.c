#include "minishell.h"
#include "parsing.h"

static void	handle_loop(t_mnsh *mnsh)
{
	char	*prompt;

	while ("apagnan")
	{
		handle_signals(mnsh->sa, &basic_signals);
		set_termios(true);
		prompt = get_prompt(getcwd(NULL, 0));
		mnsh->line = readline(prompt);
		free(prompt);
		set_termios(false);
		if (!mnsh->line)
		{
			ft_putstr_fd("\033[1A", STDOUT_FILENO);
			ft_putstr_fd(rl_prompt, STDOUT_FILENO);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
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
	free(mnsh->sa);
	ft_arrayfree(mnsh->envp);
	free(mnsh);
	return (EXIT_SUCCESS);
}
