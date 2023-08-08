/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:36:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:36:23 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charft.h"

// Counts the lenght of an array
int	ft_arraylen(char **array)
{
	int	len;

	len = 0;
	while (array && array[len])
		len++;
	return (len);
}
