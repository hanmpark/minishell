#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <stdbool.h>
#include <fcntl.h>

/* UPDATE:
* - ~ has to print the value of $HOME only if it's not a string and alone
* - instead of doing part of the expander's job in the lexer,
* do it after the parser
* - when doing the expander don't forget to treat the '*'
*/

int	count_pipes(t_token	*l_token)
{
	int	nbr;

	nbr = 0;
	while (l_token)
	{
		if (l_token->type == PIPE)
			nbr++;
		l_token = l_token->next;
	}
	return (nbr + 1);
}

int	open_file(char	*filename, int mode)
{
	int fd;

	fd = -1;
	if (mode == 0)
		fd = open(filename, O_RDONLY);
	else if (mode == 1)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == 2)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

int	check_fd(t_cmd *cmd, char *token)
{
	char	*tmp;
	int		fd;
	int		i;

	if (!is_digit(*token))
		return (-1);
	i = 0;
	while (token[i] && !is_redir(is_separator(token + i)))
		i++;
	tmp = ft_substr(token, 0, i);
	fd = ft_atoi(tmp);
	free(tmp);
	return (fd);
}

char	*here_doc(char *limiter)
{
	char	*gnl;

	gnl = 
}

void	treat_redir(t_cmd *cmd, t_token *cur, t_type type)
{
	if (type == LESS)
	{
		cmd->fdin = open_file(cur->token, 0);
		cmd->redir_in = check_fd(cmd, cur->token);
	}
	if (type == GREAT)
	{
		cmd->fdout = open_file(cur->token, 1);
		cmd->redir_out = check_fd(cmd, cur->token);
	}
	if (type == DLESS)
	{
		// here_doc;
	}
	if (type == DGREAT)
	{
		cmd->fdout = open_file(cur->token, 2);
		cmd->redir_out = check_fd(cmd, cur->token);
	}
}

t_cmd	*get_cmd(t_token *l_token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->hdoc = NULL;
	while (l_token && l_token->type != PIPE)
	{
		if (is_redir(l_token->type))
			treat_redir(cmd, l_token->next, l_token->type);
		l_token = l_token->next;
	}
	return (cmd);
}

t_token	*next_pipeline(t_token *l_token)
{
	while (l_token && l_token->type != PIPE)
		l_token = l_token->next;
	if (l_token)
		return (l_token->next);
	return (l_token);
}

bool	init_cmdtable(t_token *l_token, int nb_pipeline, t_treenode **cmdtable)
{
	int	i;

	i = 0;
	while (i < nb_pipeline)
	{
		cmdtable[i]->cmd = get_cmd(l_token);
		if (!cmdtable[i]->cmd)
			return (false);
		l_token = next_pipeline(l_token);
		i++;
	}
	return (true);
}

t_treenode	**parser(t_token *l_token)
{
	t_treenode	**cmdtable;
	int			nb_pipeline;

	cmdtable = NULL;
	if (!check_order(l_token) || !check_parentheses(l_token))
		return (NULL);
	nb_pipeline = count_pipes(l_token);
	cmdtable = ft_calloc((nb_pipeline + 1), sizeof(t_treenode *));
	if (!cmdtable)
		return (NULL);
	init_cmdtable(l_token, nb_pipeline, cmdtable);
	return (cmdtable);
}
