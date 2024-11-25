/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:52:40 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/25 16:16:55 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lex_or_pipe(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '|')
	{
		new_tkn = create_tkn(TKN_OR, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_PIPE, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_and_bg(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '&')
	{
		new_tkn = create_tkn(TKN_AND, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_BG, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_hd_rin(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '<')
	{
		new_tkn = create_tkn(TKN_HEREDOC, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_IN, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_app_rout(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos + 1] == '>')
	{
		new_tkn = create_tkn(TKN_APPEND, &input[pos], 2, pos);
		append_tkn(&tokens, new_tkn);
		pos += 2;
	}
	else
	{
		new_tkn = create_tkn(TKN_RDIR_OUT, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}

int lex_single_sym(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	if (input[pos] == ';')
	{
		new_tkn = create_tkn(TKN_SEMCOL, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	else if (input[pos] == '(')
	{
		new_tkn = create_tkn(TKN_PAREN_OP, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	else if (input[pos] == ')')
	{
		new_tkn = create_tkn(TKN_PAREN_CL, &input[pos], 1, pos);
		append_tkn(&tokens, new_tkn);
		pos++;
	}
	return (pos);
}