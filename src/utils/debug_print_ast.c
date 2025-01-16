/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:42:58 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 15:43:08 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

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
