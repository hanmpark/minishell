/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:42:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/20 00:39:03 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

extern int	g_sig;

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
	if (!mnsh)
		return (NULL);
	mnsh->is_debug = false;
	if (argc == 2 && !ft_strcmp(argv[1], "debug"))
		mnsh->is_debug = true;
	else if (argc != 1)
		return (NULL);
	mnsh->line = NULL;
	mnsh->envp = update_shlvl(ft_arraydup(envp));
	g_sig = 0;
	return (mnsh);
}

static char	*format_cwd(char *cwd)
{
	char	*formatted_cwd;
	int		count_slash;
	int		i;

	count_slash = 0;
	i = -1;
	while (count_slash < 3 && cwd[++i])
		if (cwd[i] == '/')
			count_slash++;
	formatted_cwd = ft_strdup(cwd + i);
	free(cwd);
	return (formatted_cwd);
}

/*
* Returns the prompt for minishell:
* Gets the current working directory, returns the last two directories.
*/
char	*get_prompt(char *cwd)
{
	char	*prompt;
	char	*tmp;

	if (!cwd)
		return (ft_strdup(PROMPT_COLOR "minishell" SUCCESS_COLOR " > " DEF));
	prompt = format_cwd(cwd);
	tmp = ft_strjoin(TITLE_COLOR "MINISHELL " PROMPT_COLOR "~", prompt);
	free(prompt);
	if (g_sig == 0)
		prompt = ft_strjoin(tmp, SUCCESS_COLOR " > " DEF);
	else
		prompt = ft_strjoin(tmp, ERROR_COLOR " > " DEF);
	free(tmp);
	return (prompt);
}
