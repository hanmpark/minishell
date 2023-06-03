#include "minishell.h"

/*
Once we have read the line from the prompt,...
*/

int	main(void)
{
	char	*line;

	while ("MINISHELL")
	{
		line = readline("Minishell-> ");
		free(line);
	}
	return (0);
}
