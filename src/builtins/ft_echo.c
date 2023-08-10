/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:13 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:43:56 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "builtin.h"

static bool	nl_option(char **argv, int *i)
{
	bool	is_nl_option;
	int		j;

	is_nl_option = false;
	*i = 0;
	while (argv[++(*i)] && *argv[*i] == '-')
	{
		j = 0;
		while (argv[*i][++j])
			if (argv[*i][j] != 'n')
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
int	ft_echo(char **argv)
{
	bool	nl_opt;
	int		i;

	nl_opt = nl_option(argv, &i);
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nl_opt == false)
		ft_printf("\n");
	return (0);
}
