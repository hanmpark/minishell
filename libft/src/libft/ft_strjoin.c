/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:30:45 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:37:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Takes two parameters: pointers to the two strings to be concatenated.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	dstsize;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	dstsize = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc((dstsize + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest = ft_memcpy(dest, s1, ft_strlen(s1));
	i = ft_strlen(s1);
	while (i < dstsize)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	dest[dstsize] = 0;
	return (dest);
}
