/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:33:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 17:57:58 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

int	is_argument_token(t_tkntype type)
{
	return (type == TKN_WORD || type == TKN_VAR || type == TKN_QUO_SIN
		|| type == TKN_QUO_DOU || type == TKN_BG);
}

int	is_redirection_token(t_tkntype type)
{
	return (type == TKN_RDIR_IN || type == TKN_RDIR_OUT || type == TKN_APPEND
		|| type == TKN_HEREDOC);
}

t_ast	*parser(t_token *tokens, t_alldata *all_data)
{
	t_token	*current;
	t_ast	*ast;

	current = tokens;
	ast = parse_expression(&current, all_data);
	return (ast);
}
