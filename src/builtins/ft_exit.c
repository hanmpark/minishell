#include "minishell.h"
#include "builtin.h"

#include "limits.h"

static long int	ft_atol(char *str)
{
	long int	num;
	long int	sign;

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

static bool	check_first_argument(char *arg)
{
	bool	sign;

	sign = false;
	if (*arg == '-')
	{
		sign = true;
		arg++;
	}
	if (!ft_strisdigit(arg))
		return (false);
	if (ft_strlen(arg) == 19)
	{
		if ((sign && arg[ft_strlen(arg) - 1] > '8') \
			|| (!sign && arg[ft_strlen(arg) - 1] > '7'))
			return (false);
	}
	else if (ft_strlen(arg) > 19)
		return (false);
	return (true);
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
		ft_putstr_fd(EXIT_ARGS, 2);
		return (1);
	}
	if (argv[1])
	{
		if (!check_first_argument(argv[1]))
		{
			ft_putstr_fd(ERR_EXIT, 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(NUM_ARGS_REQ, 2);
			exit(255);
		}
		exit(ft_atol(argv[1]) % 256);
	}
	exit(0);
	return (0);
}
