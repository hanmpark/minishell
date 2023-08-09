/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mnsh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:41:41 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 16:54:40 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

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

t_mnsh	*init_mnsh(int argc, char **argv, char **envp)
{
	t_mnsh	*mnsh;

	mnsh = malloc(sizeof(t_mnsh));
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

/*
* Returns the prompt for minishell:
* Gets the current working directory, returns the last two directories.
*/
char	*get_prompt(char *cwd)
{
	char	*prompt;
	char	*tmp;
	size_t	count_slash;
	size_t	cwd_len;

	if (!cwd)
		return (ft_strdup(FIRST_COLOR "minishell" LAST_COLOR " > " DEF));
	count_slash = 0;
	cwd_len = ft_strlen(cwd);
	while (count_slash < 2 && cwd[--cwd_len])
	{
		if (cwd[cwd_len] == '/')
			count_slash++;
	}
	prompt = ft_strdup(cwd + cwd_len);
	tmp = ft_strjoin(FIRST_COLOR "~", prompt);
	free(prompt);
	prompt = ft_strjoin(tmp, LAST_COLOR " > " DEF);
	free(tmp);
	free(cwd);
	return (prompt);
}
