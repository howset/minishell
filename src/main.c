/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/22 16:33:03 by hsetyamu         ###   ########.fr       */
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

int	w_cnt(char *input)
{
	int	i;
	int cnt;
	int flag;

	cnt = 0;
	flag = 0;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			flag = 0;
		else if (!flag)
		{
			flag = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

/**
 * currently the main function is still nothing
 */

int main(void)
{
	char	*input;
	t_token	*tokens;
	int		token_count;
	size_t	count;
	
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
		count = w_cnt(input);
		tokens = lexer(input, &token_count, count);
		print_tokens(tokens, token_count);
		free_tokens(tokens, token_count);
		free(input);
	}
	return (0);
}
