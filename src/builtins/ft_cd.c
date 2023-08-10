/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:11 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:48:50 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "builtin.h"
#include "putft.h"

/*
* Cd command:
* - stands for "Change Directory".
* - it is used to navigate the file system by changing the current
* working directory.
*/
int	ft_cd(char **argv, char **envp)
{
	char	*go_to_dir;

	if (ft_arraylen(argv) == 1)
	{
		go_to_dir = get_env("HOME", envp);
		if (!go_to_dir)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		go_to_dir = argv[1];
	if (chdir(go_to_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(go_to_dir);
		return (1);
	}
	return (0);
}
