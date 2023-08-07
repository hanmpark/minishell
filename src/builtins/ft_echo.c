#include "minishell.h"
#include "builtin.h"

static bool nl_option(char **av, int *i)
{
	bool	is_nl_option;
	int		j;

	is_nl_option = false;
	*i = 0;
	while (av[++(*i)] && *av[*i] == '-')
	{
		j = 0;
		while (av[*i][++j])
			if (av[*i][j] != 'n')
				return (is_nl_option);
		is_nl_option = true;
	}
	return (is_nl_option);
}

/*
* Echo command:
* - it is used to display text in the STDOUT.
* - a fundamental command for displaying information.
*/
int	ft_echo(char **av)
{
	bool	nl_opt;
	int		i;

	nl_opt = nl_option(av, &i);
	while (av[i])
	{
		ft_printf("%s", av[i]);
		if (av[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nl_opt == false)
		ft_printf("\n");
	return (0);
}
