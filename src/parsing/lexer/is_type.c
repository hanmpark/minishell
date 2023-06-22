#include "minishell.h"
#include "parsing.h"

int	is_undefined(char *str)
{
	static t_sep	undefined[] = {{"&>>", 3}, {"<<-", 3}, {"<<<", 3}, \
		{">|", 2}, {"&>", 2}, {">&", 2}, {"<&", 2}, {";", 1}, \
		{"\\", 1}};
	int				i;

	i = -1;
	while (++i < NBR_UDF)
		if (!ft_strncmp(str, undefined[i].cmpstr, undefined[i].bytes))
			return (undefined[i].bytes);
	return (0);
}

t_type	is_separator(char *str)
{
	static t_sep	sep[] = {{"<<", 2}, {">>", 2}, {"||", 2}, {"&&", 2}, \
		{"<", 1}, {">", 1}, {"|", 1}, {"(", 1}, {")", 1}, {"\'", 1}, \
		{"\"", 1}};
	int				i;

	i = -1;
	if (is_undefined(str))
		return (UNDEFINED);
	while (++i < NBR_TYPES)
		if (!ft_strncmp(str, sep[i].cmpstr, sep[i].bytes))
			return (i);
	if (!ft_strncmp(str, "&", 1))
		return (UNDEFINED);
	if (ft_isspace(*str))
		return (SPACE);
	return (WORD);
}

bool	is_redir(t_type type)
{
	return (type == DGREAT || type == DLESS || type == GREAT || type == LESS);
}

bool	is_cmdsep(t_type type)
{
	return (type == OR_IF || type == AND_IF || type == PIPE);
}