/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:07:03 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/02 11:42:38 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	while ("MINISHELL")
	{
		line = readline("Test-> ");
		printf("you typed: %s\n", line);
		free(line);
	}
	return (0);
}
