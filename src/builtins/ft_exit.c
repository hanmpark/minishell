#include "minishell.h"
#include "builtin.h"

static long int	ft_atol(char *str)
{
	long int	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (sign * num);
}

/*
* Exit command:
* It is used to terminate a shell session and return an exit
* to the parent process.
*/
int	ft_exit(char **argv)
{
	if (ft_arraylen(argv) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (argv[1])
	{
		if (!ft_strisdigit(argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		exit(ft_atol(argv[1]) % 256);
	}
	exit(0);
	return (0);
}
