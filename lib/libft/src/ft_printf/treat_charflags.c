/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_charflags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:37:35 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/08 18:37:37 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	precision_str(t_parseflags *tab, char *str, int len)
{
	while (*str && len--)
		tab->len += write(1, &*str++, 1);
}

void	left_justifystr(t_parseflags *tab, char *str, int len)
{
	int	toprint;

	toprint = tab->width - len;
	precision_str(tab, str, len);
	while (toprint-- > 0)
		tab->len += write(1, " ", 1);
}

void	widthstr(t_parseflags *tab, char *str, int len)
{
	int	toprint;

	toprint = tab->width - len;
	while (toprint-- > 0)
		tab->len += write(1, " ", 1);
	precision_str(tab, str, len);
}

void	left_justifyc(t_parseflags *tab, char c)
{
	int	toprint;

	toprint = tab->width - 1;
	tab->len += write(1, &c, 1);
	while (toprint-- > 0)
		tab->len += write(1, " ", 1);
}

void	widthc(t_parseflags *tab, char c)
{
	int	toprint;

	toprint = tab->width - 1;
	while (toprint-- > 0)
		tab->len += write(1, " ", 1);
	tab->len += write(1, &c, 1);
}
