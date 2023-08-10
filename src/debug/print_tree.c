/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:54:25 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/11 01:42:58 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

static void	print_tabs(int numtabs)
{
	int	i;

	i = 0;
	while (i < numtabs)
	{
		ft_printf("\t");
		i++;
	}
}

static void	print_single_cmd(char **args)
{
	int	i;

	if (!args)
	{
		ft_printf("NULL\n");
		return ;
	}
	ft_printf("command = ");
	i = 0;
	while (args[i])
	{
		ft_printf("[%s] ", args[i]);
		i++;
	}
	ft_printf("\n");
}

static void	print_cmds(t_cmd **cmd, int nb_pipe, int level)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		print_tabs(level);
		print_single_cmd(cmd[i]->args);
		print_tabs(level);
		ft_printf("fdin = %d\n", cmd[i]->fdin);
		print_tabs(level);
		ft_printf("fdout = %d\n", cmd[i]->fdout);
		i++;
		if (i < nb_pipe)
			ft_printf("----- PIPE -----\n");
	}
}

static void	print_tree_rec(t_tree *node, int level)
{
	if (node == NULL)
	{
		print_tabs(level);
		ft_printf("---<empty>---\n");
		return ;
	}
	if (node->cmd)
		print_cmds(node->cmd, node->nb_pipe, level);
	print_tabs(level);
	ft_printf("left\n");
	print_tree_rec(node->or_branch, level + 1);
	print_tabs(level);
	ft_printf("right\n");
	print_tree_rec(node->and_branch, level + 1);
	print_tabs(level);
	ft_printf("done\n");
}

/*
* Prints out the contents of a binary tree structure
* with tabs to make it easier to apprehend.
* Only for debugging purpose.
*/
void	print_tree(t_tree *node)
{
	if (!node)
		return ;
	ft_printf("\033[38;5;62mTREE:\033[0m\n");
	print_tree_rec(node, 0);
	ft_printf("\n");
	ft_printf("\033[38;5;182mCOMMAND OUTPUT:\033[0m\n");
}
