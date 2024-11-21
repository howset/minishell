/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/21 17:56:38 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *tokens, size_t token_count) {
	for (size_t i = 0; i < token_count; i++) {
		printf("Token %zu: ", i + 1);
		if (tokens[i].type == TKN_WORD) {
			printf("WORD, ");
		} else {
			printf("METACHARACTER, ");
		}
		printf("Value: '%s'\n", tokens[i].value);
	}
}

/**
 * currently the main function is still nothing
 */

int main(void)
{
	char	*input;
	t_token	*tokens;
	int	token_count = 0;
	
	while (1)
	{	
		input = readline("wtf-shell> "); //display prompt
		add_history(input); //add input to readline history
		if (ft_strncmp(input,"exit", 4) == 0) //exit
			exit(0);
		/* lexer(input, tokens, &token_count);
		printf("Token count:%d\n", token_count);
		for (int i = 0; i < token_count; i++) 
			printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value); */
		tokens = lexer(input, &token_count);
		print_tokens(tokens, token_count);
		free_tokens(tokens, token_count);
	}
	return (0);
}
