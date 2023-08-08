/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:36:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:36:55 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charft.h"

#include <stdlib.h>

// Duplicates a null-terminated string.
char	*ft_strdup(const char *source)
{
	int		i;
	int		count;
	char	*dest;

	i = ft_strlen(source) + 1;
	count = 0;
	dest = malloc(i * sizeof(char));
	if (!dest)
		return (0);
	while (source && source[count])
	{
		dest[count] = source[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
