#include "minishell.h"
#include "parsing.h"
#include "exit.h"
#include <stdbool.h>
#include <sys/stat.h>

/* Handling error messages and its exit status:
* - exits with 1 usually if it's not something we have to handle
* - exits with 258 for other parsing errors
*/
bool	error_token(char *token, char *err_msg, int st)
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
	g_ms.exit_status = st;
	return (false);
}

void	error_exit(char *err_src, char *msg, int st)
{
	char	*cat_str;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", err_src);
	cat_str = ft_strjoin(tmp, msg);
	free(tmp);
	ft_putstr_fd(cat_str, 2);
	free(cat_str);
	free_tree(g_ms.node);
	free_tokens(&g_ms.l_token);
	close(g_ms.stdin_fileno);
	close(g_ms.stdout_fileno);
	set_termios(false);
	exit(st);
}

void	error_not_found(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		error_exit(cmd, ERR_ENOENT, BIN_NOT_FOUND);
	error_exit(cmd, ERR_NOTFOUND, BIN_NOT_FOUND);
}

void	error_not_executable(char *cmd)
{
	struct stat	stat;

	lstat(cmd, &stat);
	if (S_ISDIR(stat.st_mode))
		error_exit(cmd, ERR_ISDIR, NOT_EXECUTABLE);
	error_exit(cmd, ERR_PERM, NOT_EXECUTABLE);
}
