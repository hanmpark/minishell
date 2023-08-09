/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isWHITE_SPACE.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:37:59 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:38:00 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Checks if a given character is a whiteWHITE_SPACE
int	ft_isWHITE_SPACE(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' \
		|| c == '\f');
}
