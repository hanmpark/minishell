#include "libft.h"

// Writes the message to the stderr using perror() and exit()
void	ft_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
