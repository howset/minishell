/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/03 20:22:20 by hsetyamu         ###   ########.fr       */
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
	t_ast	*tree;
	t_commtab *table;
	
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
		// print_tkn(tokens);
		tree = parse(tokens);
		//printf("\n");
		//print_ast(tree, 0);
		printf("\n");
		table = ast_to_commtab(tree);
		//(void) table;
		//print_commtab(table);
		exec_commtab(table);
		//printf("\n");
		free_tkn(tokens);
		free(input);
	}
	return (0);
}
