#include "minishell.h"

/*
Here you can find the implementation of the builtins.
list of builtins:
- echo (echoes the arguments) with the -n option
- cd (changes the current directory) only with a relative or absolute path
- pwd (prints the current working directory) with NO options
- export (exports a variable to the environment)
- unset (removes a variable from the environment) with NO options
- env (prints the environment variables) with NO options
- exit (exits the shell) with NO options
*/
/* Do not interpret quotes that aren't closed or special chars like ';' or '\' */

// builtin echo implementation
void	ft_echo(char *line)
{
	int		i;
	bool	n_flag;

	i = 0;
	n_flag = false;
	// check if the first argument is -n
	if (line[i] == '-' && line[i + 1] == 'n' && line[i + 2] == ' ')
	{
		n_flag = true;
		i += 3;
	}
	// print the arguments
	while (line[i])
	{
		ft_putchar_fd(line[i], 1);
		i++;
	}
	// print a newline if the -n option is not present
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}

// builtin cd (change directory) implementation using chdir()
void	ft_cd(char *line)
{
	// check if the path is valid
	if (chdir(line) == -1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
}

// builtin pwd (print working directory) implementation using getcwd()
void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
}

// builtin export implementation
/*void	ft_export(char *line)
{

}*/

// builtin unset implementation
/*void	ft_unset(char *line)
{
	// check if the variable exists
	if (getenv(line))
	{
		// removes variable from the env

	}
}*/
