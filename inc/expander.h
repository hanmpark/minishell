#ifndef EXPANDER_H
# define EXPANDER_H

char	*treat_env(char *cmd_line);
char	*expand_arg(char *line);
char	**expand_cmd(char *line);
char	*quote_str(char *line, int *cur);
char	*word_str(char *line, int *cur);

#endif