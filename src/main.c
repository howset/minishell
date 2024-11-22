/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/21 19:22:30 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *tokens, size_t token_count) 
{
	size_t i;

	i = 0;
	while (i < token_count)
	{
		printf("Token %zu: ", i + 1);
		if (tokens[i].type == TKN_WORD) {
			printf("WORD, ");
		} else {
			printf("METACHARACTER, ");
		}
		printf("Value: '%s'\n", tokens[i].value);
		i++;
	}
}

/**
 * currently the main function is still nothing
 */

int main(void)
{
	char	*input;
	t_token	*tokens;
	int		token_count;
	
	while (1)
	{	
		input = readline("wtf-shell> "); //display prompt
		add_history(input); //add input to readline history
		if (ft_strncmp(input,"exit", 4) == 0) //exit
		{
			free(input);
			exit(0);
		}
		token_count = 0;
		tokens = lexer(input, &token_count);
		print_tokens(tokens, token_count);
		free_tokens(tokens, token_count);
		free(input);
	}
	return (0);
}
