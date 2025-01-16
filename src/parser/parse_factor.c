/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_factor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:56:54 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 17:56:55 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_ast	*parse_factor(t_token **current, t_alldata *all_data)
{
	t_ast	*node;

	if ((*current)->type == TKN_PAREN_OP)
	{
		(*current) = (*current)->next;
		node = parse_expression(current, all_data);
		if ((*current)->type != TKN_PAREN_CL)
		{
			if (*current != NULL)
				syntax_error_at((*current)->position, "Unmatched parenthesis");
			else
				syntax_error_at(-1, "Unmatched parenthesis");
			return (NULL);
		}
		(*current) = (*current)->next;
	}
	else if ((*current)->type == TKN_WORD || (*current)->type == TKN_VAR)
		node = parse_command(current, all_data);
	else if ((*current)->type == TKN_QUO_DOU)
		node = parse_command(current, all_data);
	else
		return (NULL);
	return (node);
}
