/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/01 15:34:49 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**Traverse the list (forward only) and find a certain value
 * and print it to the terminal
 */
void	traverse_find(t_token *tokens, char *value)
{
	t_token	*current_node;
	int		len;

	current_node = tokens;
	len = ft_strlen(value);
	while (current_node)
	{
		if (ft_strncmp(current_node->value, value, len) == 0)
			printf("Val found: %s, %d\n", current_node->value,
				current_node->position);
		current_node = current_node->next;
	}
}

/**
 * currently the main function is still nothing
 */

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;

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
		print_ast(tree, 0);
		// traverse_find(tokens, ">>"); //
		/* 		Parser parser = {tokens, tokens};
				tree = parse(&parser);
				printf("\nAbstract Syntax Tree:\n");
				print_ast(tree, 0);
				free_ast(tree); */
		// free_tkn(tokens);
		// free(input);
	}
	return (0);
}
