#include "minishell.h"
#include "expander.h"

static bool	filecmp(t_wc *wc, char *file, const char *pattern)
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

bool	compare_front(t_wc *wc, char *file, const char *pattern)
{
	return (filecmp(wc, file, pattern));
}

bool	compare_end(t_wc *wc, char *file, const char *pattern)
{
	while (file[wc->j] && wc->j < (int)ft_strlen(file) - wc->cmplen)
		wc->j++;
	return (filecmp(wc, file, pattern));
}

bool	compare_through(t_wc *wc, char *file, const char *pattern)
{
	while (file[wc->j])
	{
		if (filecmp(wc, file, pattern))
			return (true);
		wc->j++;
	}
	return (false);
}
