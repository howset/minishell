/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:57:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/26 19:36:07 by reldahli         ###   ########.fr       */
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
	t_token	*new_tkn;
	int		pos;

	tokens = NULL;
	new_tkn = NULL;
	pos = 0;
	while (input[pos])
	{
		if (ft_isspace(input[pos]))
			pos++;
		if (input[pos] == '|')
			pos = lex_or_pipe(input, pos, &tokens, new_tkn);
		else if (input[pos] == '&')
			pos = lex_and_bg(input, pos, &tokens, new_tkn);
		else if (input[pos] == '<')
			pos = lex_hd_rin(input, pos, &tokens, new_tkn);
		else if (input[pos] == '>')
			pos = lex_app_rout(input, pos, &tokens, new_tkn);
		else if (input[pos] == ';')
			pos = lex_semi_col(input, pos, &tokens, new_tkn);
		else if (input[pos] == '(')
			pos = lex_paren_op(input, pos, &tokens, new_tkn);
		else if (input[pos] == ')')
			pos = lex_paren_cl(input, pos, &tokens, new_tkn);
		else if (input[pos] == '\'')
			pos = lex_quo_sin(input, pos, &tokens, new_tkn);
		else if (input[pos] == '"')
			pos = lex_quo_dou(input, pos, &tokens, new_tkn);
		else if (input[pos] == '$')
			pos = lex_var(input, pos, &tokens, new_tkn);
		else
			pos = lex_word(input, pos, &tokens, new_tkn);
	}
	new_tkn = create_tkn(TKN_EOF, "", 0, pos);
	append_tkn(&tokens, new_tkn);
	return (tokens);
}
