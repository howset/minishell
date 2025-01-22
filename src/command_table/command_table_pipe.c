/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 23:09:33 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

static void	process_pipe_left(t_ast *node, t_cmdtable *table, int *pipefd)
{
	t_command	*left_cmd;

	if (!node->left)
	{
		ft_fprintf(STDERR_FILENO, "Error: node->left is NULL\n");
		return ;
	}
	if (node->left->type == NODE_PIPE)
		handle_left_pipe_node(node, table, pipefd);
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
	close(pipefd[1]);
}

static void	process_pipe_right(t_ast *node, t_cmdtable *table, int *pipefd)
{
	t_command	*right_cmd;

	if (!node->right)
	{
		ft_fprintf(STDERR_FILENO, "Error: node->right is NULL\n");
		return ;
	}
	if (node->right->type == NODE_PIPE)
		handle_right_pipe_node(node, table, pipefd);
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
	close(pipefd[0]);
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
