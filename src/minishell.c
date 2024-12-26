/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/26 19:49:34 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function is the prompt for the shell. It uses the readline function
 * from the readline library to get the input from the user. It also adds the
 * input to the history list.
 * 		Takes the declared char *input from main.
 * 		Returns the input string.
 */
char	*prompt_hist(char *input)
{
	input = readline("rh-shell> ");
	if (ft_strlen(input) > 0)
		add_history(input);
	return(input);
}

/**
 * This function is the initialization step of the shell. It checks if there
 * are too many arguments and if there are, it prints an error message and
 * exits with 127. It also initializes the environment list.
 * 		Takes the arguments from the main function.
 * 		Returns nothing.
 */
t_alldata	*initialize(int argc, char *argv[], char *envp[], t_alldata *all_data)
{
	(void)argv;
	if (argc > 1)
	{
		ft_fprintf(STDERR_FILENO, "Too many args");
		exit(127);
	}
	all_data->env_head = NULL; //have to be like this or segfault
	all_data->env_list = &all_data->env_head; //have to be like this or segfault
	all_data->input = NULL;
	init_envlist(all_data->env_list, envp); //this function is momentarily in env.c
	return (all_data);
}

/**
 * currently the main function is getting confusing.
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

int	main(int argc, char *argv[], char *envp[])
{
	t_alldata	*all_data;

	all_data = malloc_perex(sizeof(t_alldata), "Malloc error on all_data");
	all_data = initialize(argc, argv, envp, all_data);
	while (1)
	{
		all_data->input = prompt_hist(all_data->input);
		if (ft_strncmp(all_data->input, "$?", 2) == 0)
			printf("%d\n", all_data->exit_stat);
		all_data->tokens = lexer(all_data->input);
		all_data->tree = parse(all_data->tokens);
		all_data->table = ast_to_command_table(all_data->tree);
		// print_command_table(all_data->table);
		all_data->exit_stat = exec_commtab(all_data->table, all_data->env_list, envp);
		free_tkn(all_data->tokens);
		free(all_data->input);
	}
	free_envlist(*all_data->env_list);
	free(all_data->env_list);
	free(all_data);
	return (0);
}
