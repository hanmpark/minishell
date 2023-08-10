/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:18 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:49:02 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "builtin.h"
#include "putft.h"
#include "isft.h"

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
	else if (*arg == '+')
		arg++;
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

static void	put_error_exit(char *arg)
{
	ft_putstr_fd(ERR_EXIT, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(NUM_ARGS_REQ, 2);
	exit(255);
}

/*
* Exit command:
* It is used to terminate a shell session and return an exit
* to the parent process.
*/
int	ft_exit(pid_t process_id, char **argv)
{
	if (process_id != 0)
		ft_printf("exit\n");
	if (argv[1])
	{
		if (!check_first_argument(argv[1]))
			put_error_exit(argv[1]);
		else if (ft_arraylen(argv) > 2)
		{
			ft_putstr_fd(EXIT_ARGS, 2);
			exit(1);
		}
		else
			exit(ft_atol(argv[1]) % 256);
	}
	exit(0);
	return (0);
}
