#include "minishell.h"

int	main(void)
{
	char	*line;

	while ("MINISHELL")
	{
		line = readline("Minishell-> ");
		printf("line length: %zu\n", ft_strlen(line));
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
