#include "listft.h"
#include <stdlib.h>

t_treenode	*ft_treenew(char **cmd, t_redirect redir, t_separator sep)
{
	t_treenode	*newtree;

	newtree = malloc(sizeof(t_treenode));
	if (!newtree)
		return (NULL);
	newtree->cmd = cmd;
	newtree->redir = redir;
	newtree->sep = sep;
	newtree->nprio = NULL;
	newtree->prio = NULL;
	return (newtree);
}
