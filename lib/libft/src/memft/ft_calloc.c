/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:38:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:39:10 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memft.h"

#include <limits.h>

/*
* Allocates a block of memory for an array and initializes all the bytes
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
