#include "minishell.h"
#include "parsing.h"
#include "exit.h"
#include <termios.h>

void	set_termios(bool set)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	if (set == true)
		termios.c_lflag &= ~ECHOCTL;
	else
		termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

static t_minishell	*init_minishell(int argc, char **argv, char **envp)
{
	t_minishell *mnsh;

	mnsh = malloc(sizeof(t_minishell));
	mnsh->is_debug = false;
	if (argc == 2 && !ft_strcmp(argv[1], "debug"))
		mnsh->is_debug = true;
	else if (argc != 1)
		return (false);
	set_termios(true);
	mnsh->line = NULL;
	mnsh->env_var = ft_arraydup(envp);
	g_exit = 0;
	return (mnsh);
}

/* To see the tokens and the tree:
*	./minishell debug
*/
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mnsh;

	mnsh = init_minishell(argc, argv, envp);
	if (!mnsh)
		return (EXIT_FAILURE);
	while ("apagnan")
	{
		mnsh->line = readline("minishell$ ");
		if (!mnsh->line)
			break ;
		handle_line(mnsh->line, &mnsh->env_var, mnsh->is_debug);
		// system("leaks minishell");
	}
	ft_arrayfree(mnsh->env_var);
	free(mnsh);
	write(1, "exit\n", 5);
	set_termios(false);
	return (EXIT_SUCCESS);
}
