/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:42:25 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:42:26 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*treat_env(t_mnsh *mnsh, char *line, bool prevent_eval);
char	**expand_arg(t_mnsh *mnsh, char *arg);
char	*extract_expand_quoted(t_mnsh *mnsh, char *arg, int *i);
char	*extract_expand_unquoted(t_mnsh *mnsh, char *arg, int *i);
char	*get_env(char *str, char **envp);

/* TREATING THE ASTERIX WILDCARD */

char	**init_entry_files(void);
char	**array_iter_globbing(t_mnsh *mnsh, char **args);
char	**match_files(char **files, const char *pattern);
bool	compare_front(t_ag *wc, char *file, const char *pattern);
bool	compare_end(t_ag *wc, char *file, const char *pattern);
bool	compare_mid(t_ag *wc, char *file, const char *pattern);

#endif