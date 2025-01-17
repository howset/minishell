/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:02 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 19:37:14 by hsetyamu         ###   ########.fr       */
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

/**
 * @brief Frees the memory allocated for an abstract syntax tree (AST).
 *
 * This function recursively frees the memory allocated for the AST nodes,
 * including their arguments and filenames. It ensures that all dynamically
 * allocated memory associated with the AST is properly released.
 *
 * @param ast A pointer to the root of the AST to be freed. If the pointer is 
 * 				NULL the function does nothing.
 */
void	free_ast(t_ast *ast)
{
	int	i;

	if (ast == NULL)
		return ;
	if (ast->args)
	{
		i = 0;
		while (i < ast->args_count)
		{
			free(ast->args[i]);
			i++;
		}
		free(ast->args);
	}
	if (ast->filename)
		free(ast->filename);
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}
