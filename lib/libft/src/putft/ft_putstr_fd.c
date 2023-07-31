#include "putft.h"
#include "charft.h"

// Writes a string to a specified file descriptor.
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
