/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:19:22 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:24:41 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks whether a given character is a valid ASCII character.
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
