/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:02 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 15:46:19 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/* create_ast_node:
 * ----------------
 * Allocates and initializes a new AST node of the given type. It sets all
 * pointers to NULL, initializes the args array with a NULL terminator,
 * sets the redirection type to invalid, and returns the newly created node.
 * Returns NULL on memory allocation failure.
 */

t_ast	*create_ast_node(t_nodetype type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = malloc(sizeof(char *));
	node->args[0] = NULL;
	node->redirection_type = TKN_INVALID;
	node->args_count = 0;
	node->filename = NULL;
	return (node);
}
