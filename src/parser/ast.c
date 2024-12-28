/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:02 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/28 22:18:45 by reldahli         ###   ########.fr       */
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
		return (NULL); // Handle malloc failure
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
/* print_indentation:
 * ------------------
 * Prints a specified indentation level by printing 'spaces' number of spaces
 * 'level' times. This visually helps represent the tree structure when printing
 * the AST.
 */

void	print_indentation(int level, int spaces)
{
	int	i;
	int	j;

	i = 0;
	while (i < level)
	{
		j = 0;
		while (j < spaces)
		{
			printf(" ");
			j++;
		}
		i++;
	}
}
/* print_redirection_info:
 * -----------------------
 * Prints the redirection details of a node if it has a valid redirection type.
 * It shows the redirection type and the filename associated with it, indented
 * according to the given level.
 */

void	print_redirection_info(t_ast *node, int level)
{
	if (node->redirection_type != TKN_INVALID)
	{
		print_indentation(level, 7);
		printf("Redirection type: %d\n", node->redirection_type);
		print_indentation(level, 7);
		printf("Filename: %s\n", node->filename);
	}
}
/* print_node_info:
 * ----------------
 * Prints the basic information of an AST node, including its type and arguments,
 * if any. Arguments and node type are printed with indentation to visually
 * represent depth. If the node has a redirection, it calls
 * print_redirection_info to display that as well.
 */

void	print_node_info(t_ast *node, int level)
{
	int	i;

	print_indentation(level, 4);
	printf("Node type: %d\n", node->type);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			print_indentation(level, 6);
			printf("Arg %d: %s\n", i, node->args[i]);
			i++;
		}
	}
	print_redirection_info(node, level);
}
/* print_ast:
 * ----------
 * Recursively prints the entire AST starting from the given node. The 'level'
 * parameter controls indentation for readability. Each node's information is
 * printed, followed by recursively printing its left and right children,
 * thereby showing the hierarchical structure of the syntax tree.
 */

void	print_ast(t_ast *node, int level)
{
	if (level == 0)
		printf("\nSyntax Tree:\n");
	if (!node)
		return ;
	print_node_info(node, level);
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}
