/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:18:48 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/25 16:41:42 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lex_quo_sin(const char *input, int pos, t_token *tokens, t_token *new_tkn)
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
		new_tkn = create_tkn(TKN_QUO_SIN, &input[start], len, start);
		append_tkn(&tokens, new_tkn);
	}
	else
	{
		perror("Unterminated single quote");
		exit(EXIT_FAILURE);
	}
	return (pos);
}

int lex_quo_dou(const char *input, int pos, t_token *tokens, t_token *new_tkn)
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
		new_tkn = create_tkn(TKN_QUO_DOU, &input[start], len, start);
		append_tkn(&tokens, new_tkn);
	}
	else
	{
		perror("Unterminated double quote");
		exit(EXIT_FAILURE);
	}
	return (pos);
}

int lex_var(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	pos++;
	while (ft_isalnum(input[pos]) || input[pos] == '_')
		pos++;
	len = pos - start;
	new_tkn = create_tkn(TKN_VAR, &input[start], len, start);
	append_tkn(&tokens, new_tkn);
	return (pos);
}

int lex_word(const char *input, int pos, t_token *tokens, t_token *new_tkn)
{
	int	start;
	int	len;

	start = pos;
	while (input[pos] && !ft_isspace(input[pos]) && !ft_strchr("|&;<>$()'\"", input[pos]))
		pos++;
	len = pos - start;
	new_tkn = create_tkn(TKN_WORD, &input[start], len, start);
	append_tkn(&tokens, new_tkn);
	return (pos);
}