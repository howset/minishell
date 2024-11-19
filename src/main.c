/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/19 14:55:20 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum {
	TOKEN_COMMANDS, //0 Token command
	TOKEN_ARGUMENTS, //1 --> anything
	TOKEN_REDIRECTIONS, //2 Token redirection
	TOKEN_END //3
} TokenType;

typedef struct {
	TokenType type;
	char value[256];
} Token;

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

void	lexer(const char *input, Token tokens[], int *token_count) 
{
	const char	*current = input;
	int			count = 0;

	while (*current != '\0') 
	{
		while (ft_isspace(*current)) // Skip whitespace
			current++;
		if (ft_isalpha(*current)) // Commands
		{
			int length = 0;
			while (ft_isalnum(*current))
			{
				tokens[count].value[length++] = *current++;
			}
			tokens[count].value[length] = '\0';
			tokens[count].type = TOKEN_COMMANDS;
			count++;
		} 
		else if (ft_isdigit(*current)) // Arguments
		{
			int length = 0;
			while (ft_isdigit(*current)) 
				tokens[count].value[length++] = *current++;
			tokens[count].value[length] = '\0';
			tokens[count].type = TOKEN_ARGUMENTS;
			count++;
		} 
		else if (*current == '|' || *current == '<' || *current == '>') // Redirs, problem: what about << & >>
		{
			tokens[count].value[0] = *current++;
			tokens[count].value[1] = '\0';
			tokens[count].type = TOKEN_REDIRECTIONS;
			count++;
		}
		else // Unknown character, skip
			current++;
	}

	// End token
	tokens[count].type = TOKEN_END;
	strcpy(tokens[count].value, "END");
	count++;

	*token_count = count;
}

int main(void)
{
	char*	input;
	Token	tokens[256];
	int		token_count = 0;
	
	while (1)
	{	
		input = readline("wtf-shell> "); //display prompt
		add_history(input); //add input to readline history
		if (ft_strncmp(input,"exit", 4) == 0) //exit
			exit(0);
		lexer(input, tokens, &token_count);
		printf("Token count:%d\n", token_count);
		for (int i = 0; i < token_count; i++) 
			printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
	}
	return 0;
}