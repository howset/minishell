/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:20:00 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/22 23:09:43 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

void	free_command_table(t_cmdtable *table)
{
	if (!table)
		return ;
	free_command(table->commands);
	free(table);
}

void	handle_left_pipe_node(t_ast *node, t_cmdtable *table, int *pipefd)
{
	t_command	*last;

	process_pipe_node(node->left, table);
	last = table->commands;
	while (last && last->next)
		last = last->next;
	if (last)
		last->pipe_write = pipefd[1];
}

void	handle_right_pipe_node(t_ast *node, t_cmdtable *table, int *pipefd)
{
	t_command	*right_cmd;

	right_cmd = process_command_node(node->right->left);
	if (right_cmd)
	{
		right_cmd->type = CMD_PIPE;
		right_cmd->pipe_read = pipefd[0];
		add_command(table, right_cmd);
	}
	process_pipe_node(node->right, table);
}
