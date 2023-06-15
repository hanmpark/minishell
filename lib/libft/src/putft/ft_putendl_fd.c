#include "putft.h"

/* Writes a string followed by a newline character to a specified
* file descriptor.
*/
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
