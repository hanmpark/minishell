/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:41:37 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/19 23:12:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARFT_H
# define CHARFT_H

# include <stdlib.h>

/* CHAR MANIPULATION */

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *source, int n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *source);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, int (*f)(char));
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_arraylen(char **array);
char	**ft_arrayjoin(char **ar1, char **ar2);
char	**ft_arraydup(char **ar);
char	**ft_arrayadd(char **ar, char *add);
char	**ft_arraynew(char *str);

#endif