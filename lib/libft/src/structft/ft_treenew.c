#include "structft.h"
#include <stdlib.h>

// Creates a new node for the tree
t_tree	*ft_treenew(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->rec_cycles = 0;
	node->initialized = 0;
	node->nb_pipe = 0;
	node->cmd = NULL;
	node->or_branch = NULL;
	node->and_branch = NULL;
	return (node);
}
