/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:53:36 by reldahli          #+#    #+#             */
/*   Updated: 2024/11/26 21:01:49 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lex_paren_op(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	new_tkn = create_tkn(TKN_PAREN_OP, &input[pos], 1, pos);
	append_tkn(tokens, new_tkn);
	pos++;
	return (pos);
}

int	lex_paren_cl(const char *input, int pos, t_token **tokens, t_token *new_tkn)
{
	new_tkn = create_tkn(TKN_PAREN_CL, &input[pos], 1, pos);
	append_tkn(tokens, new_tkn);
	pos++;
	return (pos);
}
