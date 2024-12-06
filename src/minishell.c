/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/06 19:39:32 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * currently the main function is still nothing
 */

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;
	t_commtab *table;
	int		exit_stat;
	
	if (argc > 1)
		perror("Too many args");
	(void) argv;
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
		exit_stat = exec_commtab(table, envp);
		free_tkn(tokens);
		free(input);
	}
	return (0);
}
