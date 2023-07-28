#include "minishell.h"
#include "parsing.h"

// for testing you can try use the command below:
// gcc -I../../inc/ ft_echo.c

static void n_option(int ac, char **av, int *nl_opt)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i] && i < ac)
	{
		if (av[i][0] != '-')
			break ;
		if (av[i][0] == '-')
		{
			j = 0;
			(*nl_opt)++; // increment the number of -n options
			while (av[i][++j] && av[i][0] == '-') // check if the token is -n
			{
				if (av[i][j] != 'n') // if the token is not -n, decrement the number of -n options
				{
					(*nl_opt)--;
					return ;
				}
			}
		}
		else
			break ;
	}
}

static void	put_var(char *av)
{
	char	*var;

	if (av[0] == '$' && av[1] != '\0') // print environment variables
	{
		var = getenv(av + 1);
		if (var)
			ft_printf("%s", var);
	}
	else if (av[0] == '~' && av[1] == '\0') // print home directory
		ft_printf("%s", getenv("HOME"));
	else
		ft_printf("%s", av); // print the token
}

void	ft_echo(int ac, char **av)
{
	int	i;
	int	nl_opt; // newline option

	i = 1;
	nl_opt = 0;
	n_option(ac, av, &nl_opt); // check if -n option is present
	i += nl_opt; // adds up number of options, start from the next token
	while (av[i] && i < ac)
	{
		put_var(av[i]);
		if (av[i + 1] && i + 1 < ac) // print space between arguments
			ft_printf(" ");
		i++;
	}
	if (nl_opt == 0) // print newline if -n option was not specified
		ft_printf("\n");
}

// main function to test the ft_echo builtin
/*int	main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	ft_echo(ac, av);
	return (0);
}*/
