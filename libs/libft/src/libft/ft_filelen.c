#include "get_next_line.h"

// Returns the length (line) of a file
int	ft_filelen(const char *file)
{
	char	*tmp;
	int		fd;
	int		len;

	fd = open(file, O_RDONLY);
	len = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		len++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (len);
}
