#ifndef EXPANDER_H
# define EXPANDER_H

# define THROUGH 0
# define FRONT 1
# define END 2

typedef struct s_asterix_globbing
{
	int	dotstart;
	int	cmpmode;
	int	cmplen;
	int	i;
	int	j;
}	t_wc;

char	*treat_env(char *line, bool prevent_eval);
char	**expand_arg(char *arg);
char	*get_quotestr(char *arg, int *i);
char	*word_str(char *arg, int *i);

char	**array_iter_globbing(char **args);
char	**asterix_globbing(const char *pattern);
char	**match_files(char **files, const char *pattern);
bool	compare_front(t_wc *wc, char *file, const char *pattern);
bool	compare_end(t_wc *wc, char *file, const char *pattern);
bool	compare_through(t_wc *wc, char *file, const char *pattern);

#endif