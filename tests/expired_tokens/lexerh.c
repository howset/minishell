#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <bsd/string.h>

typedef enum e_tkntype
{
	TKN_WORD,
	TKN_METACHAR,
}	t_tkntype;

typedef struct s_token{
	t_tkntype	type;
	char		*value;
}	t_token;

// Lexer function
t_token *lexer(const char *input, int *token_count) 
{
	size_t capacity = 10; // change with argc
	size_t i;
	t_token token;
	size_t start;
	size_t length;
	
	t_token *tokens = malloc(sizeof(t_token) * capacity);
	if (!tokens)
	{
		perror("Malloc failed for tokens");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (input[i] != '\0') 
	{
		if (isspace(input[i]))
			i++;
		if (isalnum(input[i]))
		{
			start = i;
			while (isalnum(input[i]))
				i++;
			length = i - start;
			token.type = TKN_WORD;
			token.value = malloc(length + 1);
			if (!token.value) 
			{
				perror("Malloc failed for token.value (words)");
				exit(EXIT_FAILURE);
			}
			strlcpy(token.value, &input[start], length + 1);
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
			token.value = malloc(length + 1);
			if (!token.value)
			{
				perror("Malloc failedfor token.value (metachars)");
				exit(EXIT_FAILURE);
			}
			strlcpy(token.value, &input[start], length + 1);
		}
		tokens[*token_count].type = token.type;
		tokens[*token_count].value = token.value; //add token to array
		(*token_count)++;
	}
	return (tokens);
}

void free_tokens(t_token *tokens, size_t token_count)
{
	size_t	i;

	i = 0;
	while (i < token_count)
		free(tokens[i].value);
	free(tokens);
}

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

int main(void)
{
	char	*input;
	t_token	*tokens;
	int	token_count = 0;
	
	while (1)
	{	
		input = readline("wtf-shell> "); //display prompt
		add_history(input); //add input to readline history
		if (strncmp(input,"exit", 4) == 0) //exit
			exit(0);
		token_count = 0;
		tokens = lexer(input, &token_count);
		print_tokens(tokens, token_count);
		free_tokens(tokens, token_count);
	}
	return (0);
}