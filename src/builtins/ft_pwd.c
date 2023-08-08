/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:18:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:18:57 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

/*
* Pwd command:
* - stands for "Print Working Directory".
* - used to display the current working directory.
*/
int	ft_pwd(void)
{
	char	buf[4096];

	if (getcwd(buf, 4096) == NULL)
	{
		perror("minishell: pwd:");
		return (1);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	return (0);
}

/* Note to self:
4096: the length of the working directory is limited to 4096 characters
in certain Linux / macOS systems. Defined by the POSIX standard.

pwd: Failure: need to check if pwd has an error message if it fails?
*/