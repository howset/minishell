/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 23:23:03 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

static void	process_pipe_left(t_ast *node, t_cmdtable *table, int *pipefd)
{
	t_command	*left_cmd;
	t_command	*last;

	if (node->left->type == NODE_PIPE)
	{
		process_pipe_node(node->left, table);
		last = table->commands;
		while (last && last->next)
			last = last->next;
		if (last)
			last->pipe_write = pipefd[1];
	}
	else
	{
		left_cmd = process_command_node(node->left);
		if (left_cmd)
		{
			left_cmd->type = CMD_PIPE;
			left_cmd->pipe_write = pipefd[1];
			add_command(table, left_cmd);
		}
	}
}

static void	process_pipe_right(t_ast *node, t_cmdtable *table, int *pipefd)
{
	t_command	*right_cmd;

	if (node->right->type == NODE_PIPE)
	{
		right_cmd = process_command_node(node->right->left);
		if (right_cmd)
		{
			right_cmd->type = CMD_PIPE;
			right_cmd->pipe_read = pipefd[0];
			add_command(table, right_cmd);
		}
		process_pipe_node(node->right, table);
	}
	else
	{
		right_cmd = process_command_node(node->right);
		if (right_cmd)
		{
			right_cmd->type = CMD_PIPE;
			right_cmd->pipe_read = pipefd[0];
			add_command(table, right_cmd);
		}
	}
}

void	process_pipe_node(t_ast *node, t_cmdtable *table)
{
	int			pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	process_pipe_left(node, table, pipefd);
	process_pipe_right(node, table, pipefd);
	table->pipe_count++;
}

t_cmdtable	*ast_to_command_table(t_ast *ast)
{
	t_cmdtable	*table;

	table = create_command_table();
	if (!table)
		return (NULL);
	ast_to_cmdtable_recursive(ast, table);
	return (table);
}
