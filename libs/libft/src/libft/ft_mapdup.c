/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:33:05 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:29:03 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	maplen(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

// Duplicates an array of strings
char	**ft_mapdup(char **map)
{
	char	**res;
	int		i;

	i = -1;
	res = malloc((maplen(map) + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (map && map[++i])
		res[i] = ft_strdup(map[i]);
	res[i] = 0;
	return (res);
}
