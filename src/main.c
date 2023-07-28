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

static bool	init_minishell(int argc, char **argv)
{
	g_ms.is_debug = false;
	if (argc == 2 && !ft_strncmp(argv[1], "debug", ft_strlen(argv[1])))
		g_ms.is_debug = true;
	else if (argc != 1)
		return (false);
	set_termios(true);
	g_ms.l_token = NULL;
	g_ms.line = NULL;
	g_ms.node = NULL;
	g_ms.exit_status = 0;
	g_ms.stdin_fileno = dup(STDIN_FILENO);
	g_ms.stdout_fileno = dup(STDOUT_FILENO);
	return (true);
}

/* To see the tokens and the tree:
*	./minishell debug
*/
int	main(int argc, char **argv, char **envp)
{
	if (!init_minishell(argc, argv))
		return (EXIT_FAILURE);
	while ("apagnan")
	{
		g_ms.line = readline("minishell$ ");
		if (!g_ms.line)
			break ;
		handle_line(g_ms.line, envp);
		// system("leaks minishell");
	}
	close(g_ms.stdin_fileno);
	close(g_ms.stdout_fileno);
	write(1, "exit\n", 5);
	set_termios(false);
	return (EXIT_SUCCESS);
}
