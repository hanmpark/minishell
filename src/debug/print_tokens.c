/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:54 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:42:46 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

static void	print_type(t_type type)
{
	if (type == DLESS)
		ft_printf("DLESS\n");
	else if (type == DGREAT)
		ft_printf("DGREAT\n");
	else if (type == OR_IF)
		ft_printf("OR_IF\n");
	else if (type == AND_IF)
		ft_printf("AND_IF\n");
	else if (type == LESS)
		ft_printf("LESS\n");
	else if (type == GREAT)
		ft_printf("GREAT\n");
	else if (type == PIPE)
		ft_printf("PIPE\n");
	else if (type == LPAR)
		ft_printf("LPAR\n");
	else if (type == RPAR)
		ft_printf("RPAR\n");
	else if (type == QUOTE)
		ft_printf("QUOTE\n");
	else if (type == DQUOTE)
		ft_printf("DQUOTE\n");
	else if (type == WORD)
		ft_printf("WORD\n");
}

// Prints out the tokens with their type (ONLY FOR DEBUGGING PURPOSE)
void	print_tokens(t_tok *l_token)
{
	int	count;

	count = 0;
	ft_printf("\n\033[38;5;62mTOKENS:\033[0m\n");
	while (l_token)
	{
		ft_printf("[%d] token = [%s] type = ", count, l_token->token);
		print_type(l_token->type);
		l_token = l_token->next;
		count++;
	}
	ft_printf("\n");
}
