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

char	*treat_env(char *line, char **envp, bool prevent_eval);
char	**expand_arg(char *arg, char **envp);
char	*extract_expand_quoted(char *arg, char **envp, int *i);
char	*extract_expand_unquoted(char *arg, char **envp, int *i);
char	*get_env(char *str, char **envp);

/* TREATING THE ASTERIX WILDCARD */

char	**init_entry_files(void);
char	**array_iter_globbing(char **args, char **envp);
char	**match_files(char **files, const char *pattern);
bool	compare_front(t_ag *wc, char *file, const char *pattern);
bool	compare_end(t_ag *wc, char *file, const char *pattern);
bool	compare_mid(t_ag *wc, char *file, const char *pattern);

#endif