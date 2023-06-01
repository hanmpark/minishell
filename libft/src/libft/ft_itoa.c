/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:03:35 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:25:27 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int			len;
	long int	nbr;

	len = 0;
	nbr = (long int)n;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	if (!nbr)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

// Converts an integer into a string.
char	*ft_itoa(int n)
{
	int			nbr_len;
	char		*str;
	long int	nbr;

	nbr_len = count_len(n);
	str = ft_calloc(nbr_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	nbr = (long int)n;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr_len--)
	{
		if (str[nbr_len] == '-')
			break ;
		str[nbr_len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
