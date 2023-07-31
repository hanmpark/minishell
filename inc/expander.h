#ifndef EXPANDER_H
# define EXPANDER_H

# define GLOB_FRONT 1
# define GLOB_MID 2
# define GLOB_END 3

typedef struct s_astglob
{
	int	dotstart;
	int	cmpmode;
	int	cmplen;
	int	i;
	int	j;
}	t_ag;

/* EXPANDING */

char	*treat_env(char *line, bool prevent_eval);
char	**expand_arg(char *arg);
char	*get_quotestr(char *arg, int *i);
char	*word_str(char *arg, int *i);

/* TREATING THE ASTERIX WILDCARD */

char	**init_entry_files(void);
char	**array_iter_globbing(char **args);
char	**match_files(char **files, const char *pattern);
bool	compare_front(t_ag *wc, char *file, const char *pattern);
bool	compare_end(t_ag *wc, char *file, const char *pattern);
bool	compare_mid(t_ag *wc, char *file, const char *pattern);

#endif