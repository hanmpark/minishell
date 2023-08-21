/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:46 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/20 00:41:44 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "putft.h"
#include "exit.h"

#include <sys/stat.h>

extern int	g_sig;

/*
* Handling error messages and its exit status:
* - exits with 1 usually if it's not something we have to handle.
* - exits with 258 for other parsing errors.
*/
bool	error_token(char *token, char *err_msg, int err_no)
{
	if (ft_strrchr(err_msg, '`'))
	{
		ft_putstr_fd(err_msg, 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd(ERR_CTOKEN, 2);
	}
	else if (!token)
		ft_putstr_fd(err_msg, 2);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd(err_msg, 2);
	}
	g_sig = err_no;
	return (false);
}

static void	error_exit(char *err_src, char *msg, int st)
{
	char	*cat_str;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", err_src);
	cat_str = ft_strjoin(tmp, msg);
	free(tmp);
	ft_putstr_fd(cat_str, 2);
	free(cat_str);
	exit(st);
}

/*
* Handling error messages and its exit status for commands that does not exist:
* - outputs the error message.
* - exits with the most adapted exit status.
*/
void	error_not_found(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		error_exit(cmd, ERR_ENOENT, BIN_NOT_FOUND);
	error_exit(cmd, ERR_NOTFOUND, BIN_NOT_FOUND);
}

/*
* Handling error messages and its exit status for commands
* that are not executable:
* - outputs the error message.
* - exits with the most adapted exit status.
*/
void	error_not_executable(char *cmd)
{
	struct stat	stat;

	lstat(cmd, &stat);
	if (S_ISDIR(stat.st_mode))
		error_exit(cmd, ERR_ISDIR, NOT_EXECUTABLE);
	else if (!S_ISDIR(stat.st_mode) && cmd[ft_strlen(cmd) - 1] == '/')
		error_exit(cmd, ERR_NODIR, NOT_EXECUTABLE);
	error_exit(cmd, ERR_PERM, NOT_EXECUTABLE);
}
