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

void	update_envp(char ***envp)
{
	char	*str;
	char	*number;
	int		i;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], "SHLVL", 5))
		{
			number = ft_itoa(ft_atoi(ft_strchr((*envp)[i], '=') + 1) + 1);
			str = ft_strjoin("SHLVL=", number);
			free(number);
			free((*envp)[i]);
			(*envp)[i] = str;
			return ;
		}
	}
	*envp = ft_arrayadd(*envp, ft_strdup("SHLVL=1"));
}

static t_minishell	*init_minishell(int argc, char **argv, char **envp)
{
	t_minishell	*mnsh;

	mnsh = malloc(sizeof(t_minishell));
	mnsh->is_debug = false;
	if (argc == 2 && !ft_strcmp(argv[1], "debug"))
		mnsh->is_debug = true;
	else if (argc != 1)
		return (false);
	set_termios(true);
	mnsh->line = NULL;
	mnsh->envp = ft_arraydup(envp);
	update_envp(&mnsh->envp);
	g_exit = 0;
	return (mnsh);
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
	t_minishell	*mnsh;

	mnsh = init_minishell(argc, argv, envp);
	if (!mnsh)
		return (EXIT_FAILURE);
	while ("apagnan")
	{
		mnsh->line = readline("minishell$ ");
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
