/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:54:54 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:24:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks whether a given character is an alphabetic character.
* It determines if the character is either an uppercase letter (A-Z) 
* or a lowercase letter (a-z).
*/
int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
