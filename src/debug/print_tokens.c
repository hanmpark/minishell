#include "minishell.h"

static void	print_type(t_type type)
{
	if (type == DLESS)
		printf("DLESS\n");
	else if (type == DGREAT)
		printf("DGREAT\n");
	else if (type == OR_IF)
		printf("OR_IF\n");
	else if (type == AND_IF)
		printf("AND_IF\n");
	else if (type == LESS)
		printf("LESS\n");
	else if (type == GREAT)
		printf("GREAT\n");
	else if (type == PIPE)
		printf("PIPE\n");
	else if (type == LPAR)
		printf("LPAR\n");
	else if (type == RPAR)
		printf("RPAR\n");
	else if (type == QUOTE)
		printf("QUOTE\n");
	else if (type == DQUOTE)
		printf("DQUOTE\n");
	else if (type == WORD)
		printf("WORD\n");
}

// Prints out the tokens with their type (ONLY FOR DEBUG PURPOSE)
void	print_tokens(t_token *l_token)
{
	int	count;

	count = 0;
	printf("\n\033[38;5;62mTOKENS:\033[0m\n");
	while (l_token)
	{
		printf("[%d] token = [%s] type = ", count, l_token->token);
		print_type(l_token->type);
		l_token = l_token->next;
		count++;
	}
	printf("\n");
}
