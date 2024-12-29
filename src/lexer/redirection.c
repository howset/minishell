/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:52:49 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/29 13:01:46 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_hd_rin(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '<')
	{
		new_tkn = create_tkn(TKN_HEREDOC, "<<", 2, pos);
		append_tkn(tokens, new_tkn);
		pos += 2;

		// Skip whitespace after heredoc operator
		while (input[pos] && ft_isspace(input[pos]))
			pos++;

		// Get the delimiter
		int start = pos;
		while (input[pos] && !ft_isspace(input[pos]))
			pos++;

		if (pos > start)
		{
			char *delimiter = ft_substr(input, start, pos - start);
			new_tkn = create_tkn(TKN_WORD, delimiter, pos - start, start);
			append_tkn(tokens, new_tkn);
			free(delimiter);
		}
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_IN, "<", 1, pos);
		append_tkn(tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int	lex_app_rout(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '>')
	{
		new_tkn = create_tkn(TKN_APPEND, &input[pos], 2, pos);
		append_tkn(tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_OUT, &input[pos], 1, pos);
		append_tkn(tokens, new_tkn);
		pos++;
	}
	return (pos);
}
