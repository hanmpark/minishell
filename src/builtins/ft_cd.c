#include "minishell.h"
#include "parsing.h"

static void	home_chdir(const char *name)
{
	char	*home;

	home = getenv(name);
	if (!home)
		return ;
	chdir(home);
}

static void	my_chdir(const char *path)
{
	if (chdir(path) == -1)
	{
		// perror function
		return ;
	}
}

void	ft_cd(int ac, char **av)
{
	char	*home;
	char	*path;
	long	len_av;
	long	len_home;

	// need to get current working directory
	if (ac == 1 || (av[1][0] == '~' && av[1][1] == '\0'))
		home_chdir("HOME");
	else if (ac > 1 && (av[1][0] == '~' && av[1][1] == '/'))
	{
		home = getenv("HOME");
		len_av = ft_strlen(av[1]);
		len_home = ft_strlen(home);
		path = malloc(sizeof(char) * len_av);
		if (!path)
			return ;
		ft_strlcpy(path, home, len_home);
		ft_strlcat(path, av[1] + len_home, len_av - len_home);
	}
	if (path)
		my_chdir(path);
	else if (ac > 1 && av[1][0] != '~')
		my_chdir(av[1]);
	// need to add 0 value for success command execution: $? = 0
	// didn't test this function yet, so it's purely theoretical
}
