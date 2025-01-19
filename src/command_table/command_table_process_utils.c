/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_process_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:48:31 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/19 18:52:22 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

void	process_ast_node(t_ast *ast, t_cmdtable *table)
{
	t_command	*cmd;
	t_ast		*cmd_node;

	if (ast->type == NODE_COMMAND)
	{
		cmd = process_command_node(ast);
		if (cmd)
			add_command(table, cmd);
	}
	else if (ast->type == NODE_PIPE)
		process_pipe_node(ast, table);
	else if (ast->type == NODE_REDIRECTION)
	{
		cmd_node = find_command_node(ast);
		cmd = process_command_node(cmd_node);
		if (cmd_node && cmd)
		{
			process_redirection_node(ast, cmd);
			add_command(table, cmd);
		}
	}
}

t_command	*get_last_command(t_cmdtable *table)
{
	t_command	*current;

	if (!table || !table->commands)
		return (NULL);
	current = table->commands;
	while (current->next)
		current = current->next;
	return (current);
}

void	ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table)
{
	t_command	*cmd;

	if (!ast || !table)
		return ;
	if (ast->type == NODE_SEQUENCE)
	{
		ast_to_cmdtable_recursive(ast->left, table);
		ast_to_cmdtable_recursive(ast->right, table);
		return ;
	}
	if (ast->type == NODE_SUBSHELL)
	{
		cmd = process_subshell_node(ast);
		if (cmd)
			add_command(table, cmd);
		return ;
	}
	if (ast->type == NODE_AND || ast->type == NODE_OR)
	{
		ast_to_cmdtable_recursive(ast->left, table);
		cmd = get_last_command(table);
		if (cmd)
			cmd->next_operator = ast->type;
		ast_to_cmdtable_recursive(ast->right, table);
		return ;
	}
	process_ast_node(ast, table);
}

