/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:19:39 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:29:44 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compares two memory blocks up to a specified number of bytes.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str1;
	int				i;

	str = (unsigned char *)s1;
	str1 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str[i] != str1[i])
			return ((str[i] - str1[i]));
		i++;
	}
	return (0);
}
