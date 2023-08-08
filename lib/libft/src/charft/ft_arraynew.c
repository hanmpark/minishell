/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraynew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:36:24 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:36:26 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charft.h"
#include "memft.h"

// Creates a new array of strings with an element
char	**ft_arraynew(char *str)
{
	char	**array;

	array = ft_calloc(1, sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_arrayadd(array, str);
	return (array);
}
