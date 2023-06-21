#include "minishell.h"

// check for each builtin commands
void	builtin_cmds(t_minishell *ms)
{
	if (!ft_strncmp(ms->table->token, "echo", 5))
		ft_echo(ms->table);
	else if (!ft_strncmp(ms->table->token, "cd", 3))
		ft_cd(ms->table);
	else if (!ft_strncmp(ms->table->token, "pwd", 4))
		ft_pwd(ms->table);
	else if (!ft_strncmp(ms->table->token, "export", 7))
		ft_export(ms->table);
	else if (!ft_strncmp(ms->table->token, "unset", 6))
		ft_unset(ms->table);
	else if (!ft_strncmp(ms->table->token, "env", 4))
		ft_env(ms->table);
	else if (!ft_strncmp(ms->table->token, "exit", 5))
		ft_exit(ms->table);
}
