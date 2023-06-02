/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:39:52 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/01 10:25:04 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if a given character is a printable character.
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
