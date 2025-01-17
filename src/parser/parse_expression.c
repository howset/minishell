/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:52:38 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 17:52:47 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

t_ast	*parse_expression(t_token **current, t_alldata *all_data)
{
	t_ast		*node;
	t_nodetype	type;
	t_ast		*op_node;

	node = parse_pipe(current, all_data);
	while (*current && ((*current)->type == TKN_AND
			|| (*current)->type == TKN_OR || (*current)->type == TKN_SEMCOL))
	{
		if (!node)
		{
			syntax_error_at((*current)->position,
				"Unexpected logical operator without a preceding command");
			return (NULL);
		}
		type = check_optype((*current)->type);
		op_node = handle_opnode(current, all_data, node, type);
		if (!op_node)
			return (NULL);
		node = op_node;
	}
	return (node);
}

t_nodetype	check_optype(t_tkntype token_type)
{
	if (token_type == TKN_AND)
		return (NODE_AND);
	if (token_type == TKN_OR)
		return (NODE_OR);
	return (NODE_SEQUENCE);
}

t_ast	*handle_opnode(t_token **current, t_alldata *all_data, t_ast *left_node,
	t_nodetype type)
{
	t_ast	*op_node;

	op_node = create_ast_node(type);
	if (!op_node)
		return (NULL);
	op_node->left = left_node;
	(*current) = (*current)->next;
	op_node->right = parse_pipe(current, all_data);
	if (!op_node->right)
	{
		if (*current)
			syntax_error_at((*current)->position,
				"Expected a command after logical operator");
		else
			syntax_error_at(-1, "Expected a command after logical operator");
		return (NULL);
	}
	return (op_node);
}
