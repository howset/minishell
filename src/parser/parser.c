/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:33:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 19:47:28 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/**
 * @brief Checks if the given token type is an argument token.
 *
 * This function determines whether the provided token type is one of the
 * argument tokens. The argument tokens include:
 * - TKN_WORD: A word token.
 * - TKN_VAR: A variable token.
 * - TKN_QUO_SIN: A single-quoted string token.
 * - TKN_QUO_DOU: A double-quoted string token.
 * - TKN_BG: A background token.
 *
 * @param type The token type to check.
 * @return int Returns 1 if the token type is an argument token, otherwise 0.
 */
int	is_argument_token(t_tkntype type)
{
	return (type == TKN_WORD || type == TKN_VAR || type == TKN_QUO_SIN
		|| type == TKN_QUO_DOU || type == TKN_BG);
}

/**
 * @brief Checks if the given token type is a redirection token.
 *
 * This function determines whether the provided token type corresponds to
 * any of the redirection tokens, which include input redirection, output
 * redirection, append redirection, and heredoc.
 *
 * @param type The token type to check.
 * @return Non-zero value if the token type is a redirection token, zero 
 * otherwise.
 */
int	is_redirection_token(t_tkntype type)
{
	return (type == TKN_RDIR_IN || type == TKN_RDIR_OUT || type == TKN_APPEND
		|| type == TKN_HEREDOC);
}

/**
 * @brief Parses a list of tokens into an abstract syntax tree (AST).
 *
 * This function takes a list of tokens and parses them into an AST, which
 * represents the syntactic structure of the input. The parsing process
 * starts from the given tokens and uses the provided all_data for additional
 * context or configuration.
 *
 * @param tokens A pointer to the first token in the list of tokens to be 
 * parsed.
 * @param all_data A pointer to a structure containing additional data 
 * required for parsing.
 * @return A pointer to the root of the generated AST.
 */
t_ast	*parser(t_token *tokens, t_alldata *all_data)
{
	t_token	*current;
	t_ast	*ast;

	current = tokens;
	ast = parse_expression(&current, all_data);
	return (ast);
}
