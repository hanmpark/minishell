#ifndef PUTFT_H
# define PUTFT_H

# include <unistd.h>

/* OUTPUT TO FD */

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif