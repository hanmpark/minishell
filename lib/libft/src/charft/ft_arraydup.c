/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:36:18 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:36:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charft.h"
#include "memft.h"

// Duplicates an array of strings
char	**ft_arraydup(char **ar)
{
	char	**dup;
	int		i;

	dup = ft_calloc(ft_arraylen(ar) + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (ar[i])
	{
		dup[i] = ft_strdup(ar[i]);
		i++;
	}
	return (dup);
}
