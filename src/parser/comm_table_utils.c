/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:48:32 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/25 15:28:53 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/* create_simcomm:
 * ---------------
 * This function initializes the t_simmcom struct.
 * Takes a node from the syntax tree as the argument.
 * Returns an initialized struct where everything is empty except
 * the args field.
 */

t_simcomm	*create_simcomm(t_ast *node)
{
	t_simcomm	*cmd;

	cmd = malloc_perex(sizeof(t_simcomm), "Malloc error on create_simcomm");
	cmd->args = node->args;
	cmd->in_redir = NULL;
	cmd->out_redir = NULL;
	if (ft_strncmp(node->args[node->args_count - 1], "&", 1) == 0)
		cmd->is_bg = 1;
	else
		cmd->is_bg = 0;
	return (cmd);
}

/* traverse_ast:
 * -------------
 * This function serves as the main entry point for recursively traversing the
 * AST. It uses the node type to decide which specialized handler function to
 * call. This allows separation of logic based on node type:
 * - NODE_COMMAND: Calls handle_command_node.
 * - NODE_REDIRECTION: Calls handle_redirection_node.
 * - Otherwise: Calls handle_compound_nodes.
 *
 * If the node is NULL, it returns an error. Otherwise, it attempts to handle
 * the node and returns the result of the called handler function.
 */

int	traverse_ast(t_ast *node, t_commtab *table)
{
	if (!node)
		return (1);
	if (node->type == NODE_COMMAND)
		return (handle_command_node(node, table));
	else if (node->type == NODE_REDIRECTION)
		return (handle_redirection_node(node, table));
	else
		return (handle_compound_nodes(node, table));
}
/* handle_redirection_node:
 * -------------------------
 * This function handles NODE_REDIRECTION type nodes. It first traverses the
 * left subtree (which should represent a command node or another redirection
 * leading to a command), then applies the discovered redirection filename to
 * the last added command in the table. This ensures the redirection is
 * associated with the correct command.
 */

int	handle_redirection_node(t_ast *node, t_commtab *table)
{
	t_simcomm	*last_cmd;

	traverse_ast(node->left, table);
	if (table->count > 0)
	{
		last_cmd = &table->commands[table->count - 1];
		if (node->redirection_type == TKN_RDIR_IN)
			last_cmd->in_redir = ft_strdup(node->filename);
		else if (node->redirection_type == TKN_RDIR_OUT
			|| node->redirection_type == TKN_APPEND)
			last_cmd->out_redir = ft_strdup(node->filename);
	}
	return (0);
}

/* handle_compound_nodes:
 * -----------------------
 * This function handles all other node types that are not simple commands or
 * direct redirections. These include sequences (NODE_SEQUENCE), logical
 * connectors (NODE_AND, NODE_OR), pipes (NODE_PIPE), subshells (NODE_SUBSHELL),
 * and invalid nodes (NODE_INVALID).
 *
 * Depending on the node type, it will:
 * - For NODE_SEQUENCE and NODE_PIPE: traverse left and right subtrees.
 * - For NODE_AND: traverse the left subtree, and if successful, traverse right.
 * - For NODE_OR: traverse the left subtree, and if fails, traverse right.
 * - For NODE_SUBSHELL: traverse the left subtree.
 * - For NODE_INVALID: print an error message and return failure.
 */

int	handle_compound_nodes(t_ast *node, t_commtab *table)
{
	if (node->type == NODE_SEQUENCE || node->type == NODE_PIPE)
	{
		traverse_ast(node->left, table);
		traverse_ast(node->right, table);
	}
	else if (node->type == NODE_AND)
	{
		if (traverse_ast(node->left, table) == 0)
			traverse_ast(node->right, table);
	}
	else if (node->type == NODE_OR)
	{
		if (traverse_ast(node->left, table) == 0)
			traverse_ast(node->right, table);
	}
	else if (node->type == NODE_SUBSHELL)
		traverse_ast(node->left, table);
	else if (node->type == NODE_INVALID)
	{
		fprintf(stderr, "Invalid AST node detected.\n");
		return (1);
	}
	return (0);
}
