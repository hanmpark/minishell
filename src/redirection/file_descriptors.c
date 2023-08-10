/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:52:45 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 14:40:32 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exit.h"

#include <fcntl.h>

static int	open_file(char	*filename, int mode)
{
	int	fd;

	fd = -1;
	if (mode == READ)
		fd = open(filename, O_RDONLY);
	else if (mode == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static void	reset_fd(t_cmd *cmd, t_tok *l_token)
{
	if (l_token->type == LESS || l_token->type == DLESS)
	{
		if (cmd->fdin != STDIN_FILENO)
		{
			close(cmd->fdin);
			cmd->fdin = STDIN_FILENO;
		}
	}
	else if (l_token->type == GREAT || l_token->type == DGREAT)
	{
		if (cmd->fdout != STDOUT_FILENO)
		{
			close(cmd->fdout);
			cmd->fdout = STDOUT_FILENO;
		}
	}
}

/*
* Handles the redirection(s) of a command:
* - extracts token type: get the type of the current token to identify
* the redirection type.
* - resets file descriptors: resets command file descriptors to their defaults.
* - checks file name: verifies the next token contains a valid file name.
* - opens the specified file updating the command structure's
* file descriptors accordingly.
*/
bool	handle_redirection(t_mnsh *mnsh, t_cmd *cmd, t_tok **l_token)
{
	t_type	type;

	type = (*l_token)->type;
	reset_fd(cmd, *l_token);
	*l_token = (*l_token)->next;
	if (type != DLESS && !check_filename(mnsh, *l_token))
		return (false);
	if (type == LESS)
		cmd->fdin = open_file((*l_token)->token, READ);
	else if (type == DLESS)
		cmd->fdin = here_doc(mnsh, (*l_token)->token);
	else if (type == GREAT)
		cmd->fdout = open_file((*l_token)->token, TRUNC);
	else if (type == DGREAT)
		cmd->fdout = open_file((*l_token)->token, APPEND);
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (error_token((*l_token)->token, ERR_ENOENT, NO_HANDLE));
	if (cmd->fdin == HERE_DOC_SIG)
		return (false);
	*l_token = (*l_token)->next;
	return (true);
}
