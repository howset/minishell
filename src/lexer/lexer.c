/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:57:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/15 18:13:50 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**The lexer function iterates over the input string and whenever a defined
 * symbol is encountered, a corresponding function is called to create a node
 * that contains an appropriate token, jumping over whitespaces. This will be
 * appended to the list. The list will contain all the tokens (the type, value,
 *  and position).
 * 		Takes the input from readline as the parameter.
 * 		Returns the tokens.
 */
t_token	*lexer(const char *input)
{
	t_token	*tokens;
	int		pos;

	tokens = NULL;
	pos = 0;
	while (input[pos])
	{
		if (ft_isspace(input[pos]))
			pos++;
		else
			pos = handle_token(input, pos, &tokens);
	}
	append_tkn(&tokens, create_tkn(TKN_EOF, "", 0, pos));
	return (tokens);
}

int	handle_token(const char *input, int pos, t_token **tokens)
{
	t_token	*new_tkn;

	new_tkn = NULL;
	if (input[pos] == '|')
		return (lex_or_pipe(input, pos, tokens, new_tkn));
	else if (input[pos] == '&')
		return (lex_and_bg(input, pos, tokens, new_tkn));
	else if (input[pos] == '<')
		return (lex_hd_rin(input, pos, tokens, new_tkn));
	else if (input[pos] == '>')
		return (lex_app_rout(input, pos, tokens, new_tkn));
	else if (input[pos] == ';')
		return (lex_semi_col(input, pos, tokens, new_tkn));
	else if (input[pos] == '(')
		return (lex_paren_op(input, pos, tokens, new_tkn));
	else if (input[pos] == ')')
		return (lex_paren_cl(input, pos, tokens, new_tkn));
	else if (input[pos] == '\'')
		return (lex_quo_sin(input, pos, tokens, new_tkn));
	else if (input[pos] == '"')
		return (lex_quo_dou(input, pos, tokens, new_tkn));
	else if (input[pos] == '$')
		return (lex_var(input, pos, tokens, new_tkn));
	else
		return (lex_word(input, pos, tokens, new_tkn));
}
