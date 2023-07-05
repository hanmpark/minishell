#include "minishell.h"
#include "expander.h"
#include "parsing.h"

// Treats the asterix wildcard
char	**wildcards(char *pattern)
{

}

// test
int	main(int argc, char *argv[]) {
	if (argc < 2)
		return 1;
	for (int i = 0; argv[i] != NULL; i++) {
		wildcards(argv[i]);
	}
	return 0;
}
