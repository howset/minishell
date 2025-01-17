/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:54:30 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 20:00:50 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/**
 * parse_command - Parses a command from the token stream and constructs an
 * AST node.
 * @current: A pointer to the current token in the token stream.
 * @all_data: A pointer to the structure containing all relevant data.
 *
 * This function creates a new AST node of type NODE_COMMAND and processes
 * tokens from the token stream to populate the node. It continues processing
 * tokens as long as the current token is of type TKN_WORD, TKN_VAR, TKN_QUO_SIN,
 * TKN_QUO_DOU, or TKN_BG. If the node creation fails, it returns NULL.
 *
 * Return: A pointer to the created AST node, or NULL if node creation fails.
 */
t_ast	*parse_command(t_token **current, t_alldata *all_data)
{
	t_ast	*node;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	while (*current && ((*current)->type == TKN_WORD
			|| (*current)->type == TKN_VAR || (*current)->type == TKN_QUO_SIN
			|| (*current)->type == TKN_QUO_DOU || (*current)->type == TKN_BG))
	{
		if (process_tkn(current, node, all_data))
			continue ;
	}
	return (node);
}

/**
 * process_tkn - Processes a token and updates the AST node with the token's
 * value.
 * @current: Double pointer to the current token being processed.
 * @node: Pointer to the AST node that will be updated with the token's value.
 * @all_data: Pointer to the structure containing all necessary data for
 * processing.
 *
 * This function processes a token and updates the AST node with the token's
 * value. If the token is of type TKN_VAR and its value is "$EMPTY", the
 * function skips the token and returns 1. Otherwise, it increments the
 * argument count of the node, reallocates memory for the node's arguments,
 * sanitizes the token's value, and adds it to the node's arguments. If memory
 * allocation fails, the function prints an error message and exits the
 * program. The function returns 0 on success.
 *
 * Return: 1 if the token is "$EMPTY", 0 otherwise.
 */
int	process_tkn(t_token **current, t_ast *node, t_alldata *all_data)
{
	char	*sanitized;

	if ((*current)->type == TKN_VAR
		&& ft_strcmp((*current)->value, "$EMPTY") == 0)
	{
		(*current) = (*current)->next;
		return (1);
	}
	node->args_count++;
	node->args = ft_realloc(node->args,
			sizeof(char *) * node->args_count,
			sizeof(char *) * (node->args_count + 1));
	if (!node->args)
	{
		perror("ft_realloc");
		exit(EXIT_FAILURE);
	}
	sanitized = sanitize_text((*current)->value, all_data);
	node->args[node->args_count - 1] = ft_strdup(sanitized);
	free(sanitized);
	node->args[node->args_count] = NULL;
	(*current) = (*current)->next;
	return (0);
}
