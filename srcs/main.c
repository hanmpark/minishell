/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquetat- <kquetat-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:07:03 by hanmpark          #+#    #+#             */
/*   Updated: 2023/06/02 11:21:17 by kquetat-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	line = readline("Test-> ");
	if (!line)
		printf("\n");
	else
	{
		printf("you typed: %s\n", line);
		free(line);
	}
	return (0);
}
