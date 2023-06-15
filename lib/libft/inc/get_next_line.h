#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
void	ft_freeall(char *buf, char *line, char *stash);
void	*ft_calloc(size_t count, size_t size);
char	*ft_bufferjoin(char *s1, char *s2);
char	*ft_linetrim(char *str);

#endif
