/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:37:56 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:37:58 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "isft.h"

// Checks if a given character is part of a env_var
int	ft_isenv(char c)
{
	return (ft_isalnum(c) || c == '_');
}
