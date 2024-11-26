/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:52:49 by reldahli          #+#    #+#             */
/*   Updated: 2024/11/26 21:05:17 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_hd_rin(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '<')
	{
		new_tkn = create_tkn(TKN_HEREDOC, &input[pos], 2, pos);
		append_tkn(tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_IN, &input[pos], 1, pos);
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
