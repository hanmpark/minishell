#include "minishell.h"
#include <stdbool.h>


void	lexer(char *cmd_line)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(cmd_line))
	{
		if (cmd_line[i] == '|')

		i++;
	}
}

static char	*check_env(char *cmd_line)
{
	
}

/* Scans the input text character by character and groups characters
* into meaningful units, such as keywords, identifiers, operators, and literals
*/
void	parsing(char *cmd_line)
{
	char	*line_env;

	line_env = check_env(cmd_line);
}
