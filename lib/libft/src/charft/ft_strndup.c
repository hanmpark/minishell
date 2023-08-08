/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:37:04 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:37:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charft.h"

#include <stdlib.h>

// Duplicates n number of bytes in a null-terminated string.
char	*ft_strndup(const char *source, int n)
{
	char	*dest;
	int		count;

	if (n > (int)ft_strlen(source))
		return (NULL);
	else if (n == 0)
		return (ft_strdup(""));
	dest = malloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	count = 0;
	while (count < n)
	{
		dest[count] = source[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
