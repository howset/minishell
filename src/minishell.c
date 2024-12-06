/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/06 19:30:59 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**Traverse the list (forward only) and find a certain value
 * and print it to the terminal
 */
void	traverse_find(t_token *tokens, char *value)
{
	t_token	*current_node;
	int		len;

	current_node = tokens;
	len = ft_strlen(value);
	while (current_node)
	{
		if (ft_strncmp(current_node->value, value, len) == 0)
			printf("Val found: %s, %d\n", current_node->value,
				current_node->position);
		current_node = current_node->next;
	}
}

/**
 * Print the command table for debugging purposes
 */
void	print_command_table(t_cmdtable *table)
{
	t_command *cmd;
	t_redirection *redir;
	int i;

	if (!table)
		return ;
	printf("\nCommand Table:\n");
	printf("Total commands: %d\n", table->cmd_count);
	printf("Total pipes: %d\n", table->pipe_count);

	cmd = table->commands;
	while (cmd)
	{
		printf("\nCommand:\n");
		printf("Type: %d\n", cmd->type);
		printf("Arguments: ");
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("%s ", cmd->args[i]);
			i++;
		}
		printf("\n");

		if (cmd->pipe_read != -1)
			printf("Pipe read fd: %d\n", cmd->pipe_read);
		if (cmd->pipe_write != -1)
			printf("Pipe write fd: %d\n", cmd->pipe_write);

		redir = cmd->redirections;
		while (redir)
		{
			printf("Redirection: type=%d, file=%s\n", redir->type, redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	printf("\n");
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_ast		*tree;
	t_cmdtable	*table;

	while (1)
	{
		input = readline("wtf-shell> ");
		if (!input)  // Handle Ctrl+D (EOF)
		{
			printf("\nGoodbye!\n");
			break;
		}
		add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			exit(0);
		}
		tokens = lexer(input);
		if (tokens)
		{
			tree = parse(tokens);
			if (tree)
			{
				table = ast_to_command_table(tree);
				if (table)
				{
					print_command_table(table);
					free_command_table(table);
				}
				free_ast(tree);
			}
			// free_tkn(tokens);  // Uncomment when implemented
		}
		free(input);
	}
	return (0);
}
