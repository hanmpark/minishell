#include "minishell.h"
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	while ("MINISHELL")
	{
		line = readline("Test-> ");
		printf("you typed: %s\n", line);
		free(line);
	}
	return (0);
}
