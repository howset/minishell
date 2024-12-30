/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:52:36 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/30 04:52:38 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_cmdtable	*create_command_table(void)
{
	t_cmdtable	*table;

	table = malloc(sizeof(t_cmdtable));
	if (!table)
		return (NULL);
	table->commands = NULL;
	table->cmd_count = 0;
	table->pipe_count = 0;
	return (table);
}

char	**duplicate_args(char **args, int count)
{
	char	**new_args;
	int		i;

	if (!args || count == 0)
	{
		new_args = malloc(sizeof(char *));
		if (!new_args)
			return (NULL);
		new_args[0] = NULL;
		return (new_args);
	}
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			while (--i >= 0)
				free(new_args[i]);
			free(new_args);
			return (NULL);
		}
		i++;
	}
	new_args[count] = NULL;
	return (new_args);
}

t_command	*create_command(char **args, t_cmd_type type)
{
	t_command	*cmd;
	int			count;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	// Count arguments
	count = 0;
	while (args && args[count])
		count++;
	// Duplicate arguments
	cmd->args = duplicate_args(args, count);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redirections = NULL;
	cmd->type = type;
	cmd->pipe_read = -1;
	cmd->pipe_write = -1;
	cmd->next = NULL;
	return (cmd);
}

t_redirection	*create_redirection(t_tkntype type, char *file)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	add_command(t_cmdtable *table, t_command *cmd)
{
	t_command	*current;

	if (!table->commands)
		table->commands = cmd;
	else
	{
		current = table->commands;
		while (current->next)
			current = current->next;
		current->next = cmd;
	}
	table->cmd_count++;
}

void	add_redirection(t_command *cmd, t_redirection *redir)
{
	t_redirection	*current;

	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

t_command	*process_command_node(t_ast *node)
{
	t_command	*cmd;
	char		**default_args;

	if (!node)
		return (NULL);
	if (node->type == NODE_REDIRECTION)
	{
		// Process the command part (left child)
		cmd = process_command_node(node->left);
		if (!cmd)
		{
			// Create empty command if none exists
			default_args = malloc(sizeof(char *) * 2);
			if (!default_args)
				return (NULL);
			default_args[0] = ft_strdup("");
			default_args[1] = NULL;
			cmd = create_command(default_args, CMD_SIMPLE);
			free(default_args[0]);
			free(default_args);
		}
		// Create and add redirection
		process_redirection_node(node, cmd);
		return (cmd);
	}
	// Original command processing
	if (!node->args || !node->args[0])
	{
		default_args = malloc(sizeof(char *) * 2);
		if (!default_args)
			return (NULL);
		default_args[0] = ft_strdup("");
		default_args[1] = NULL;
		cmd = create_command(default_args, CMD_SIMPLE);
		free(default_args[0]);
		free(default_args);
		return (cmd);
	}
	return (create_command(node->args, CMD_SIMPLE));
}

void	process_pipe_node(t_ast *node, t_cmdtable *table)
{
	t_command	*left_cmd;
	t_command	*right_cmd;
	int			pipefd[2];
	t_command	*last;

	if (pipe(pipefd) == -1)
		return ;
	// Process left side
	if (node->left->type == NODE_PIPE)
	{
		process_pipe_node(node->left, table);
		// Get the last command from the table to set its pipe_write
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
	// Process right side
	if (node->right->type == NODE_PIPE)
	{
		// Create the first command of the right pipeline
		right_cmd = process_command_node(node->right->left);
		if (right_cmd)
		{
			right_cmd->type = CMD_PIPE;
			right_cmd->pipe_read = pipefd[0];
			add_command(table, right_cmd);
		}
		// Process the rest of the pipeline
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
	table->pipe_count++;
}

void	process_redirection_node(t_ast *node, t_command *cmd)
{
	t_redirection	*redir;

	// If the left node is a redirection, process it first
	if (node->left && node->left->type == NODE_REDIRECTION)
		process_redirection_node(node->left, cmd);
	// Then add this redirection
	redir = create_redirection(node->redirection_type, node->filename);
	if (redir)
		add_redirection(cmd, redir);
}

t_command	*process_subshell_node(t_ast *node)
{
	t_command	*cmd;

	cmd = process_command_node(node->left);
	if (cmd)
		cmd->type = CMD_SUBSHELL;
	return (cmd);
}

t_ast	*find_command_node(t_ast *node)
{
	while (node && node->type == NODE_REDIRECTION)
		node = node->left;
	return (node);
}

void	ast_to_cmdtable_recursive(t_ast *ast, t_cmdtable *table)
{
	t_command	*cmd;
	t_ast		*cmd_node;

	if (!ast || !table)
		return ;
	switch (ast->type)
	{
	case NODE_COMMAND:
		cmd = process_command_node(ast);
		if (cmd)
			add_command(table, cmd);
		break ;
	case NODE_PIPE:
		process_pipe_node(ast, table);
		break ;
	case NODE_REDIRECTION:
		cmd_node = find_command_node(ast);
		if (cmd_node)
		{
			cmd = process_command_node(cmd_node);
			if (cmd)
			{
				process_redirection_node(ast, cmd);
				add_command(table, cmd);
			}
		}
		break ;
	case NODE_SEQUENCE:
		ast_to_cmdtable_recursive(ast->left, table);
		ast_to_cmdtable_recursive(ast->right, table);
		break ;
	case NODE_SUBSHELL:
		cmd = process_subshell_node(ast);
		if (cmd)
			add_command(table, cmd);
		break ;
	default:
		break ;
	}
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

void	free_redirection(t_redirection *redir)
{
	t_redirection	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_command(t_command *cmd)
{
	t_command	*next;
	int			i;

	while (cmd)
	{
		next = cmd->next;
		free_redirection(cmd->redirections);
		// Free command arguments
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		free(cmd);
		cmd = next;
	}
}

void	free_command_table(t_cmdtable *table)
{
	if (!table)
		return ;
	free_command(table->commands);
	free(table);
}
