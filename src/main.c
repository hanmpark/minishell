#include "minishell.h"

/*
* Once we have read the line from the prompt,...
*/

int	main(void)
{
	char	*line;

	while ("apagnan")
	{
		line = readline("minishell $ ");
		parsing(line);
		printf("line after parsing = %s\n", line);
		free(line);
	}
	return (0);
}
