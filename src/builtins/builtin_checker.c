#include "minishell.h"

// check for each builtin commands
void	builtin_cmds(void)
{
	if (!ft_strncmp(g_ms.l_token->token, "echo", 5))
		ft_echo(g_ms.l_token);
	else if (!ft_strncmp(g_ms.l_token->token, "cd", 3))
		ft_cd(g_ms.l_token);
	else if (!ft_strncmp(g_ms.l_token->token, "pwd", 4))
		ft_pwd(g_ms.l_token);
	else if (!ft_strncmp(g_ms.l_token->token, "export", 7))
		ft_export(g_ms.l_token);
	else if (!ft_strncmp(g_ms.l_token->token, "unset", 6))
		ft_unset(g_ms.l_token);
	else if (!ft_strncmp(g_ms.l_token->token, "env", 4))
		ft_env(g_ms.l_token);
	else if (!ft_strncmp(g_ms.l_token->token, "exit", 5))
		ft_exit(g_ms.l_token);
}
