/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:52:38 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 19:42:15 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"
/**
 * parse_expression - Parses an expression from the token stream.
 * @current: A pointer to the current token pointer.
 * @all_data: A pointer to the structure containing all necessary data.
 *
 * This function parses an expression by first parsing a pipe and then
 * checking for logical operators (AND, OR, SEMICOLON). If a logical operator
 * is found, it ensures that there is a preceding command and then handles
 * the operator node accordingly. If any errors are encountered, such as a
 * logical operator without a preceding command, a syntax error is reported.
 *
 * Return: A pointer to the root of the abstract syntax tree (AST) representing
 *         the parsed expression, or NULL if an error occurs.
 */

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

/**
 * @brief Determines the node type based on the token type.
 *
 * This function takes a token type as input and returns the corresponding
 * node type. It maps specific token types to their respective node types.
 *
 * @param token_type The type of the token to be checked.
 * @return The corresponding node type:
 *         - NODE_AND if the token type is TKN_AND
 *         - NODE_OR if the token type is TKN_OR
 *         - NODE_SEQUENCE for any other token type
 */
t_nodetype	check_optype(t_tkntype token_type)
{
	if (token_type == TKN_AND)
		return (NODE_AND);
	if (token_type == TKN_OR)
		return (NODE_OR);
	return (NODE_SEQUENCE);
}

/**
 * handle_opnode - Handles the creation of an operator node in the AST.
 * @current: Double pointer to the current token in the token list.
 * @all_data: Pointer to the structure containing all necessary data.
 * @left_node: Pointer to the left child node of the operator node.
 * @type: The type of the operator node to be created.
 *
 * This function creates an operator node of the specified type and attaches
 * the given left child node to it. It then advances the current token pointer
 * and parses the right child node using the parse_pipe function. If the right
 * child node cannot be parsed, it reports a syntax error indicating that a
 * command was expected after the logical operator.
 *
 * Return: Pointer to the created operator node, or NULL if an error occurs.
 */
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
