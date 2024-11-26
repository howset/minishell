/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:18:48 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/26 19:31:50 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


int lex_var(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	len = pos - start;
	new_tkn = create_tkn(TKN_VAR, &input[start], len, start);
	append_tkn(tokens, new_tkn);
	return (pos);
}

int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	while ((input[pos] && !ft_isspace(input[pos])) && 
					!ft_strchr("|&;<>$()'\"", input[pos]))
		pos++;
	len = pos - start;
	new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
	append_tkn(tokens, new_tkn);
	return (pos);
}

/* // New function to handle TKN_WORD
int lex_word(const char *input, int pos, t_token **tokens) {
	int start = pos;
	t_token *new_tkn;

	// Find the end of the word
	while (input[pos] && !ft_isspace(input[pos]) && !ft_strchr("|&;<>$()'\"", input[pos]))
		pos++;

	// Calculate the length and create a token
	int len = pos - start;
	new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
	append_tkn(tokens, new_tkn);

	return pos;  // Return the updated position
} */

/* int lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn) {
    int start = pos;

    // Find the end of the word
    while (input[pos] && !ft_isspace(input[pos]) && !ft_strchr("|&;<>$()'\"", input[pos]))
        pos++;

    // Calculate the length and create a token
    int len = pos - start;
    new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
    append_tkn(tokens, new_tkn);

    return pos;  // Return the updated position
} */