#ifndef EXPANDER_H
# define EXPANDER_H

# define THROUGH 0
# define FRONT 1
# define END 2

typedef struct	s_wildcards
{
	int	dotstart;
	int	cmpmode;
	int	cmplen;
	int	i;
	int	j;
}	t_wc;

char	*treat_env(char *line);
char	*expand_arg(char *line);
char	**expand_cmd(char *line);
char	*get_quotestr(char *line, int *cur);
char	*word_str(char *line, int *cur);

char	**wildcards(const char *pattern);
char	**match_files(char **files, const char *pattern);
void	init_wc(t_wc *wc, const char *pattern);
bool	compare_front(t_wc *wc, char *file, const char *pattern);
bool	compare_end(t_wc *wc, char *file, const char *pattern);
bool	compare_through(t_wc *wc, char *file, const char *pattern);

#endif