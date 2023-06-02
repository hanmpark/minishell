/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:40:07 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:19:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
