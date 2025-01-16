/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:52:49 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/15 18:07:40 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_hd_rin(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '<')
	{
		pos = handle_heredoc(input, pos, tokens);
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_IN, "<", 1, pos);
		append_tkn(tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int	handle_heredoc(const char *input, int pos, t_token **tokens)
{
	int		start;
	char	*delimiter;
	t_token	*new_tkn;

	new_tkn = create_tkn(TKN_HEREDOC, "<<", 2, pos);
	append_tkn(tokens, new_tkn);
	pos += 2;
	while (input[pos] && ft_isspace(input[pos]))
		pos++;
	start = pos;
	while (input[pos] && !ft_isspace(input[pos]))
		pos++;
	if (pos > start)
	{
		delimiter = ft_substr(input, start, pos - start);
		new_tkn = create_tkn(TKN_WORD, delimiter, pos - start, start);
		append_tkn(tokens, new_tkn);
		free(delimiter);
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
