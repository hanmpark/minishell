/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:36:30 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/19 23:12:38 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charft.h"

#include <stdlib.h>

static size_t	count_words(char const *str, int (*f)(char))
{
	size_t	count;

	count = 0;
	while (*str && f(*str))
		str++;
	if (*str == 0)
		return (0);
	while (*str)
	{
		count++;
		while (*str && !f(*str))
			str++;
		while (*str && f(*str))
			str++;
	}
	return (count);
}

static char	*cpy_to_tab(char const *str, size_t size)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = malloc((size + 1) * sizeof(char));
	if (!tab)
		return (0);
	while (i < size)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

// Splits a string into an array of substrings based on a specified delimiter.
char	**ft_split(char const *s, int (*f)(char))
{
	char	**tab;
	size_t	j;
	size_t	count;

	if (!s)
		return (0);
	count = count_words(s, f);
	tab = malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (*s)
	{
		if (*s && !f(*s))
		{
			j = 0;
			while (s[j] && !f(s[j]))
				j++;
			*(tab++) = cpy_to_tab(s, j);
			s += j;
		}
		else
			s++;
	}
	*tab = 0;
	return (tab - count);
}
