#include "minishell.h"

/*
* Once we have read the line from the prompt,...
*/

int	main(void)
{
	char	*line;

	while ("apagnan")
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		parsing(line);
		free(line);
	}
	return (0);
}
