/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/06 17:54:13 by hsetyamu         ###   ########.fr       */
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
	int		exit_stat;
	
	while (1)
	{
		input = readline("wtf-shell> ");
		add_history(input);
		if (ft_strncmp(input, "$?", 2) == 0)
			printf("%d\n", exit_stat);
		tokens = lexer(input);
		//print_tkn(tokens);
		tree = parse(tokens);
		//print_ast(tree, 0);
		table = ast_to_commtab(tree);
		//print_commtab(table);
		exit_stat = exec_commtab(table);
		free_tkn(tokens);
		free(input);
	}
	return (0);
}
