/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:38:07 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:38:08 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// Sets a specified block of memory to zero by writing null bytes.
void	ft_bzero(void *s, size_t n)
{
	char	*var;

	var = s;
	while (n)
	{
		*var++ = 0;
		n--;
	}
}
