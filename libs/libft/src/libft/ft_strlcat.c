/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:01:57 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:38:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Appends a null-terminated string from the source to the destination,
* while ensuring that the destination buffer does not overflow.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dsize;
	size_t	ssize;
	size_t	i;

	if ((!dst || !src) && !size)
		return (0);
	if (ft_strlen(dst) >= size)
		return (ft_strlen(src) + size);
	dsize = ft_strlen(dst);
	ssize = ft_strlen(src);
	i = 0;
	while (src[i] && dsize + i < size - 1)
	{
		dst[dsize + i] = src[i];
		i++;
	}
	dst[dsize + i] = '\0';
	return (dsize + ssize);
}
