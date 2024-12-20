/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:26:20 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/20 17:18:15 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/* ast_to_commtab:
 * ---------------
 * This function aims to convert a syntax tree to a command table.
 * Takes the resulting t_ast tree from the parser.
 * Returns a command table that contains (row-by-row) simple commands.
 * These can then be executed sequentially.
 */

t_commtab	*ast_to_commtab(t_ast *tree)
{
	t_commtab	*table;

	table = create_commtab();
	traverse_ast(tree, table);
	return (table);
}

/* create_commtab:
 * ---------------
 * This function initializes the t_commtab struct.
 * Takes no args.
 * Returns an empty initialized struct.
 */

t_commtab	*create_commtab(void)
{
	t_commtab	*table;

	table = malloc_perex(sizeof(t_commtab), "Malloc error on create_commtab");
	table->commands = NULL;
	table->count = 0;
	return (table);
}

/* handle_command_node:
 * --------------------
 * This function handles NODE_COMMAND type nodes in the AST. It expands the
 * command table to accommodate a new simple command, creates a simcomm struct
 * from the node information, and assigns input/output redirections if present.
 * It then increments the command count in the table.
 */

int	handle_command_node(t_ast *node, t_commtab *table)
{
	t_simcomm	*cmd;

	table->commands = ft_realloc(table->commands, sizeof(t_simcomm)
			* (table->count + 1));
	if (!table->commands)
		return (1);
	cmd = create_simcomm(node);
	if (node->redirection_type == TKN_RDIR_IN)
		cmd->in_redir = ft_strdup(node->filename);
	else if (node->redirection_type == TKN_RDIR_OUT
		|| node->redirection_type == TKN_APPEND)
		cmd->out_redir = ft_strdup(node->filename);
	table->commands[table->count] = *cmd;
	table->count++;
	return (0);
}

/* print_commtab:
 * --------------
 * This function just prints the content of the created command table. It runs
 * through the list/table row by row.
 * 		Takes the command table as argument.
 * 		Returns nothing.
 */

void	print_commtab(t_commtab *table)
{
	int	i;
	int	j;

	printf("\n");
	printf("Command Table:\n");
	i = 0;
	while (i < table->count)
	{
		printf("Command %d:\n", i + 1);
		j = 0;
		while (table->commands[i].args[j])
		{
			printf("  Arg[%d]: %s\n", j, table->commands[i].args[j]);
			j++;
		}
		if (table->commands[i].in_redir)
			printf("  Input Redirection: %s\n", table->commands[i].in_redir);
		if (table->commands[i].out_redir)
			printf("  Output Redirection: %s\n", table->commands[i].out_redir);
		if (table->commands[i].is_bg == 1)
			printf("  Background: Yes\n");
		else
			printf("  Background: No\n");
		i++;
	}
}
