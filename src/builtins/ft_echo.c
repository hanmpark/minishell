#include "minishell.h"
#include "parsing.h"

// for testing you can try use the command below:
// gcc -I../../inc/ ft_echo.c

static void n_option(char **av, int *nl_opt)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
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

int	ft_echo(char **av)
{
	int	i;
	int	nl_opt; // newline option

	i = 1;
	nl_opt = 0;
	n_option( av, &nl_opt); // check if -n option is present
	i += nl_opt; // adds up number of options, start from the next token
	while (av[i])
	{
		ft_printf("%s", av[i]);
		if (av[i + 1]) // print space between arguments
			ft_printf(" ");
		i++;
	}
	if (nl_opt == 0) // print newline if -n option was not specified
		ft_printf("\n");
	return (0);
}

// main function to test the ft_echo builtin
/*int	main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	ft_echo(ac, av);
	return (0);
}*/
