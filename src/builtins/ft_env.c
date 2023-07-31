#include "minishell.h"
#include "parsing.h"

/* implementation de la commande env en utilisant char **envp.
* dans l'idée ce serai de faire ça.
* env: une commande interne dans bash qui permet d'afficher les variables
* d'environnement.
*/
void	ft_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	ft_env(envp);
	return (0);
}
