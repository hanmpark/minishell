#ifndef STRUCTFT_H
# define STRUCTFT_H

# include <stdbool.h>

typedef struct	s_token
{
	char			*token;
	int				type;
	int				par_id;
	struct s_token	*next;
}	t_token;

typedef struct	s_cmd
{
	char			**args;
	int				redir_in;
	int				redir_out;
	int				fdin;
	int				fdout;
}	t_cmd;

typedef struct	s_treenode
{
	unsigned int		rec_cycles;
	int					initialized;
	int					nb_pipe;
	int					par_id;
	struct s_cmd		**cmd;
	struct s_treenode	*or_branch;
	struct s_treenode	*and_branch;
}	t_treenode;

/* CHAINED LIST MANIPULATION */

t_token			*ft_toknew(char *token, int type);
void			ft_tokadd_front(t_token **lst, t_token *new);
void			ft_tokadd_back(t_token **lst, t_token *new);
t_token			*ft_toklast(t_token *lst);

/* BINARY TREE MANIPULATION */

t_treenode		*ft_treenew(void);
void			ft_treeadd_left(t_treenode **node, t_treenode *new);
void			ft_treeadd_right(t_treenode **node, t_treenode *new);
void			ft_treereset(t_treenode *node);
void			ft_treeset_cycles(t_treenode *node);
t_cmd			*ft_cmdnew(void);
int				ft_countpipe(t_token *l_token);
t_treenode		*ft_addnode(t_treenode *table, t_treenode *add, t_token mode);

#endif