/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:57:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/26 21:10:37 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**The lexer function just iterates over the input string and whenever a defined
 * symbol is encountered, a corresponding function is called to create a node
 * that contains an appropriate token. This will be appended to the list.
 * The (singly/doubly linked) list will contain all the tokens (the type, value,
 * and position).
 * Currently I have no idea why the TKN_WORD cant be wrapped properly in the
 * lex_word function. So I left it as it is.
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
