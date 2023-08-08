/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 08:53:34 by hanmpark          #+#    #+#             */
/*   Updated: 2023/08/01 08:53:36 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static bool	filecmp(t_ag *wc, char *file, const char *pattern)
{
	if (!wc->dotstart && file[0] == '.')
		return (false);
	if (!ft_strncmp(file + wc->j, pattern + wc->i, wc->cmplen))
	{
		wc->j += wc->cmplen;
		return (true);
	}
	return (false);
}

bool	compare_front(t_ag *wc, char *file, const char *pattern)
{
	return (filecmp(wc, file, pattern));
}

bool	compare_end(t_ag *wc, char *file, const char *pattern)
{
	while (file[wc->j] && wc->j < (int)ft_strlen(file) - wc->cmplen)
		wc->j++;
	return (filecmp(wc, file, pattern));
}

bool	compare_mid(t_ag *wc, char *file, const char *pattern)
{
	while (file[wc->j])
	{
		if (filecmp(wc, file, pattern))
			return (true);
		wc->j++;
	}
	return (false);
}
