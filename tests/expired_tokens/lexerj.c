/* void	lexer(const char *input, Token tokens[], int *token_count) 
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

//	*token_count = count;
} */