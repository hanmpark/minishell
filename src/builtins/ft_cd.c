#include "minishell.h"
#include "parsing.h"

int	ft_cd(char **av)
{
	if (chdir(av[0]) == -1)
	{
		perror("minishell: cd:");
		return (1);
	}
	return (0);
}
