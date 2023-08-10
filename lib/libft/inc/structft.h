/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:41:50 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/10 20:08:04 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTFT_H
# define STRUCTFT_H

# include <stdbool.h>

typedef struct s_token
{
	char			*token;
	int				type;
	int				par_id;
	struct s_token	*next;
}	t_tok;

typedef struct s_cmd
{
	char	**args;
	int		pid;
	int		fdin;
	int		fdout;
}	t_cmd;

typedef struct s_treenode
{
	unsigned int		rec_cycles;
	int					initialized;
	int					nb_pipe;
	int					par_id;
	struct s_cmd		**cmd;
	struct s_treenode	*or_branch;
	struct s_treenode	*and_branch;
}	t_tree;

/* CHAINED LIST MANIPULATION */

t_tok	*ft_toknew(char *token, int type);
void	ft_tokadd_front(t_tok **lst, t_tok *new);
void	ft_tokadd_back(t_tok **lst, t_tok *new);
t_tok	*ft_toklast(t_tok *lst);

/* BINARY TREE MANIPULATION */

t_tree	*ft_treenew(void);
void	ft_treeadd_left(t_tree **node, t_tree *new);
void	ft_treeadd_right(t_tree **node, t_tree *new);
void	ft_treereset(t_tree *node);
void	ft_treeset_cycles(t_tree *node);
t_cmd	*ft_cmdnew(void);
int		ft_countpipe(t_tok *l_token);

#endif