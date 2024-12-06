/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/26 21:01:23 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * currently the main function is still nothing
 */

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("wtf-shell> ");
		add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(0);
		}
		tokens = lexer(input);
		print_tkn(tokens);
		free_tkn(tokens);
		free(input);
	}
	return (0);
}
