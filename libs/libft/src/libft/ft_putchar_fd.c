#include "libft.h"

// Writes a character to a specified file descriptor.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
