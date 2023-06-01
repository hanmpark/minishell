/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:30:10 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:47:40 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Converts a given lowercase character
* to its corresponding uppercase representation.
*/
int	ft_toupper(int character)
{
	if (character >= 97 && character <= 122)
		character -= 32;
	return (character);
}
