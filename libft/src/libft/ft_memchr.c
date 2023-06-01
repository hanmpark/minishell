/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:36:26 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:29:29 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Searches for the first occurrence of a specified byte value
* in a memory block.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	char	ch;
	char	*var;
	int		i;

	ch = (char)c;
	i = 0;
	var = (char *)s;
	while (n--)
	{
		if (var[i] == ch)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
