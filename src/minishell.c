/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/16 18:22:26 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * currently the main function is getting confusing.
 */

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;
	t_commtab *table;
	int		exit_stat;
	t_env	*env_head; //pointer to the head of the linked list
	t_env	**env_list; //pointer to the head pointer

	if (argc > 1)
	{
		ft_fprintf(STDERR_FILENO, "Too many args");
		exit(127);
	}
	(void) argv;
	env_head = NULL; //have to be like this or segfault
	env_list = &env_head; //have to be like this or segfault
	init_envlist(env_list, envp); //this function is momentarily in env.c
	while (1)
	{
		input = readline("rh-shell> ");
		if (input && *input)
			add_history(input);
		if (ft_strncmp(input, "$?", 2) == 0)
			printf("%d\n", exit_stat);
		tokens = lexer(input);
		//print_tkn(tokens);
		tree = parse(tokens);
		//print_ast(tree, 0);
		table = ast_to_commtab(tree);
		//print_commtab(table);
		exit_stat = exec_commtab(table, env_list, envp);
		free_tkn(tokens);
		free(input);
	}
	//free_envlist(env_list);
	return (0);
}
