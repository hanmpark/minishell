/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:37:41 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:37:43 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Checks whether a given character is alphanumeric, meaning it is either
* an alphabetic character (a-z, A-Z) or a digit (0-9).
*/
int	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) || \
		(c >= '0' && c <= '9'));
}
