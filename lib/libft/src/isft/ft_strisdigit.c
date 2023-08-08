/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:38:01 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:38:03 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "isft.h"

// Checks in the given string if it only contains digits.
int	ft_strisdigit(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}
