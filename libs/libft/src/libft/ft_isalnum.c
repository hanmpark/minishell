/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:56:44 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:23:07 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks whether a given character is alphanumeric, meaning it is either
* an alphabetic character (a-z, A-Z) or a digit (0-9).
*/
int	ft_isalnum(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) || \
		(c >= '0' && c <= '9'));
}
