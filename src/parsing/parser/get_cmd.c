#include "minishell.h"
#include "parsing.h"
#include "error.h"

static int	count_args(t_token *cur)
{
	int	len;

	len = 0;
	while (cur && !is_redir(cur->type) && !is_cmdsep(cur->type))
	{
		len++;
		cur = cur->next;
	}
	return (len);
}

static char	**get_cmdargs(t_token *cur)
{
	char	**args;
	int		i;

	args = ft_calloc(count_args(cur) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (cur && !is_redir(cur->type) && !is_cmdsep(cur->type))
	{
		args[i++] = ft_strdup(cur->token);
		cur = cur->next;
	}
	return (args);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	return (cmd);
}

t_cmd	*get_cmd(t_token *l_token)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	while (l_token && !is_cmdsep(l_token->type))
	{
		if (is_redir(l_token->type))
			l_token = treat_redir(cmd, l_token, l_token->type);
		else
		{
			cmd->args = get_cmdargs(l_token);
			l_token = next_token(l_token);
		}
	}
	return (cmd);
}
