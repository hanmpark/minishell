/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:22:47 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:19:46 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/* Allocates a block of memory for an array and initializes all the bytes
* to zero.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*var;

	if (count > UINT_MAX)
		return (NULL);
	var = malloc(count * size);
	if (!var)
		return (NULL);
	ft_bzero(var, count * size);
	return (var);
}
