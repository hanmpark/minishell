#include "structft.h"
#include <stdlib.h>

/* Add a node to the tree depending on:
* - the parentheses' priorities
* - the logical operators "&&" or "||"
*/
t_treenode	*ft_addnode(t_treenode *table, t_treenode *add, t_token mode)
{
	if (!table)
		return (NULL);
	if (table->par_id == mode.par_id || !mode.par_id)
	{
		if (mode.type == 3)
			ft_treeadd_right(&table, add);
		else if (mode.type == 2)
			ft_treeadd_left(&table, add);
		return (table);
	}
	if (ft_addnode(table->and_branch, add, mode) || \
		ft_addnode(table->or_branch, add, mode))
		return (table);
	return (table);
}