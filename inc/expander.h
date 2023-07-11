#ifndef EXPANDER_H
# define EXPANDER_H

# define NORM 0
# define FRONT 1
# define END 2

typedef struct	s_wildcards
{
	int	frontend;
	int	cmplen;
	int	i;
	int	j;
}	t_wc;

char	*treat_env(char *cmd_line);
char	*expand_arg(char *line);
char	**expand_cmd(char *line);
char	*quote_str(char *line, int *cur);
char	*word_str(char *line, int *cur);

#endif