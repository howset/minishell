/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:52:57 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/29 01:06:08 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_quo_sin(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (input[pos] && input[pos] != '\'')
		pos++;
	if (input[pos] == '\'')
	{
		pos++;
		len = pos - start;
		new_tkn = create_tkn(TKN_QUO_SIN, &input[start+1], len-2, start);
		append_tkn(tokens, new_tkn);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "lexer: Unterminated single quote");
	}
	return (pos);
}

int	lex_quo_dou(const char *input, int pos,
		t_token **tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (input[pos] && input[pos] != '"')
		pos++;
	if (input[pos] == '"')
	{
		pos++;
		len = pos - start;
		new_tkn = create_tkn(TKN_QUO_DOU, &input[start]+1, len-2, start);
		append_tkn(tokens, new_tkn);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "lexer: Unterminated double quote");
	}
	return (pos);
}
