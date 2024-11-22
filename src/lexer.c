/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:30:54 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/22 14:56:36 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

// Lexer function
t_token *lexer(const char *input, int *token_count) 
{
	size_t i;
	size_t start;
	size_t length;
	
	static t_token tokens[ARG_LEN]; //malloc tokens?
	
	i = 0;
	while (input[i] != '\0') 
	{
		if (ft_isspace(input[i]))
			i++;
		t_token token;
		if (ft_isalnum(input[i]))
		{
			start = i;
			while (ft_isalnum(input[i]))
				i++;
			length = i - start;
			token.type = TKN_WORD;
			token.value = malloc_perex(length + 1, "Failed on words");
			ft_strlcpy(token.value, &input[start], length + 1);
		}
		else
		{
			start = i;
			if (input[i] == '<' && input[i + 1] == '<')
				i += 2;
			else if (input[i] == '>' && input[i + 1] == '>')
				i += 2;
			else
				i++; //others ('|', '<', '>')
			length = i - start;
			token.type = TKN_METACHAR;
			token.value = malloc_perex(length + 1, "Failed on chars");
			ft_strlcpy(token.value, &input[start], length + 1);
		}
		if (*token_count < ARG_LEN)
		{
			tokens[*token_count] = token;
			(*token_count)++;
		} else
		{
			printf("Too many tokens\n");
			free(token.value);
			break;
		}
	}
	return (tokens);
}

void free_tokens(t_token *tokens, size_t token_count)
{
	size_t	i;

	i = 0;
	//printf("executing free\n");
	while (i < token_count)
	{
		free(tokens[i].value);
		i++;
	}
}