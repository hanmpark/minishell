/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:00:30 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:46:52 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Converts a given uppercase character to its corresponding
* lowercase representation.
*/
int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
		character += 32;
	return (character);
}
