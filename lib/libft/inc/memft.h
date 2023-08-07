#ifndef MEMFT_H
# define MEMFT_H

# include <stdlib.h>

/* MEM MANIPULATION */

void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_arrayfree(char **ar);

#endif