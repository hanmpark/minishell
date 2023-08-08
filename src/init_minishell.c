/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:41:41 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 14:03:24 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <termios.h>

void	set_termios(bool set)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	if (set == true)
		termios.c_lflag &= ~(ICANON | ECHOCTL);
	else
		termios.c_lflag |= ICANON | ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

static char	**update_shlvl(char **envp)
{
	char	*str;
	char	*number;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
		{
			number = ft_itoa(ft_atoi(ft_strchr(envp[i], '=') + 1) + 1);
			str = ft_strjoin("SHLVL=", number);
			free(number);
			free(envp[i]);
			envp[i] = str;
			return (envp);
		}
	}
	envp = ft_arrayadd(envp, ft_strdup("SHLVL=1"));
	return (envp);
}

t_minishell	*init_minishell(int argc, char **argv, char **envp)
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
	mnsh->envp = update_shlvl(ft_arraydup(envp));
	g_exit = 0;
	return (mnsh);
}
