#ifndef LISTFT_H
# define LISTFT_H

# include <stdbool.h>

typedef struct s_cmdtable
{
	char				*token;
	int					type;
	struct s_cmdtable	*next;
}	t_cmdtable;

typedef struct s_treenode
{
	char				**tokens;
	int					return_val;
	int					redir;
	struct s_treenode	*tree;
	struct s_treenode	*or_branch;
	struct s_treenode	*and_branch;
}	t_treenode;

/* CHAINED LIST MANIPULATION */

t_cmdtable	*ft_lstnew(char *token, int type);
void	ft_lstadd_front(t_cmdtable **lst, t_cmdtable *new);
void	ft_lstadd_back(t_cmdtable **lst, t_cmdtable *new);
int		ft_lstsize(t_cmdtable *lst);
t_cmdtable	*ft_lstlast(t_cmdtable *lst);
void	ft_lstdelone(t_cmdtable *lst, void (*del)(void *));
void	ft_lstclear(t_cmdtable **lst, void (*del)(void *));
void	ft_lstiter(t_cmdtable *lst, void (*f)(void *));
t_cmdtable	*ft_lstmap(t_cmdtable *lst, void *(*f)(void *), void (*del)(void *));

/* BINARY TREE MANIPULATION */
t_treenode	*ft_treenew(t_cmdtable *tokens, int redir);
void	ft_treeadd_left(t_treenode *node, t_treenode *new, int pass);
void	ft_treeadd_right(t_treenode *node, t_treenode *new, int pass);

#endif