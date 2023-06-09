#ifndef STRUCTFT_H
# define STRUCTFT_H

# include <stdbool.h>

typedef struct	s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct	s_cmd
{
	char			**args;
	int				redir_in;
	int				redir_out;
	int				fdin;
	int				fdout;
	unsigned int	par_id;
	int				par_last;
}	t_cmd;

typedef struct	s_treenode
{
	unsigned int		depth;
	int					initialized;
	struct s_cmd		*cmd;
	struct s_treenode	*or_branch;
	struct s_treenode	*and_branch;
}	t_treenode;

/* CHAINED LIST MANIPULATION */

t_token		*ft_lstnew(char *token, int type);
void		ft_lstadd_front(t_token **lst, t_token *new);
void		ft_lstadd_back(t_token **lst, t_token *new);
int			ft_lstsize(t_token *lst);
t_token		*ft_lstlast(t_token *lst);
void		ft_lstdelone(t_token *lst, void (*del)(void *));
void		ft_lstclear(t_token **lst, void (*del)(void *));
void		ft_lstiter(t_token *lst, void (*f)(void *));

/* BINARY TREE MANIPULATION */

t_treenode		*ft_treenew(t_cmd *cmd);
void			ft_treeadd_left(t_treenode **node, t_treenode *new);
void			ft_treeadd_right(t_treenode **node, t_treenode *new);
void			ft_treereset(t_treenode *node);
void			ft_treeset_depth(t_treenode *node);
t_cmd			*ft_cmdnew(void);
unsigned int	ft_count_pipeline(t_token *l_token);

#endif