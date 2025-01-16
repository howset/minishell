/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:18:48 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/15 18:09:30 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_var(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (ft_isalnum(input[pos]) || input[pos] == '_' || input[pos] == '?')
		pos++;
	len = pos - start;
	new_tkn = create_tkn(TKN_VAR, &input[start], len, start);
	append_tkn(tokens, new_tkn);
	return (pos);
}

int	handle_quotes(const char *input, int pos)
{
	char	quote;

	quote = input[pos];
	while (input[++pos] != quote)
	{
		if (input[pos] == '\0')
		{
			ft_fprintf(STDERR_FILENO, "lexer: Unterminated quote");
			return (pos);
		}
	}
	return (pos);
}

int	lex_word(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	int		start;
	int		len;

	start = pos;
	while ((input[pos] && !ft_isspace(input[pos]))
		&& !ft_strchr("|&;<>()", input[pos]))
	{
		if (input[pos] == '=')
		{
			pos++;
			if (input[pos] == '"' || input[pos] == '\'')
			{
				pos = handle_quotes(input, pos);
			}
		}
		pos++;
	}
	len = pos - start;
	new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
	append_tkn(tokens, new_tkn);
	return (pos);
}
