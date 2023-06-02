/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestr_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:39:42 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:22:30 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees each substring and the array of strings itself
void	ft_freestr_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array)
	{
		while (str_array && str_array[i])
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
}
