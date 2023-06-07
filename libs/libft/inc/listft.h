#ifndef LISTFT_H
# define LISTFT_H

# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef enum s_separator
{
	NONE,
	PIPE,
	AND,
	OR,
	PRIO
}	t_separator;

typedef struct s_treenode
{
	char				**cmd;
	enum s_separator	sep;
	struct s_treenode	*nprio;
	struct s_treenode	*prio;
}	t_treenode;

/* CHAINED LIST MANIPULATION */

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* BINARY TREE MANIPULATION */
t_treenode	*ft_treenew(char **cmd, t_separator sep);

#endif