/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/13 16:40:30 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*fancy_prompt(void)
{
	char	*wdir;
	char	*temp;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*prompt;

	wdir = getcwd(NULL, 0);
	temp = ft_strjoin(YEL BOLD, "rh-shell> ");
	temp1 = ft_strjoin(BLU BOLD, wdir);
	temp2 = ft_strjoin(temp1, RES);
	temp3 = ft_strjoin(temp, temp2);
	prompt = ft_strjoin(temp3, "\n$> ");
	free(wdir);
	free(temp);
	free(temp1);
	free(temp2);
	free(temp3);
	return (prompt);
}

/**
 * This function is the prompt for the shell. It uses the readline function
 * from the readline library to get the input from the user. It also adds the
 * input to the history list.
 * 		Takes the declared char *input from main.
 * 		Returns the input string.
 * 		if (!input) // Handle ctrl-D (EOF)
 */
char	*prompt_hist(char *input)
{
	char	*prompt;

	prompt = fancy_prompt();
	input = readline(prompt);
	if (!input)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	free(prompt);
	return (input);
}

/**
 * This function is the initialization step of the shell. It checks if there
 * are too many arguments and if there are, it prints an error message and
 * exits with 127. It also initializes the environment list.
 * 		Takes the arguments from the main function.
 * 		Returns nothing.
 */
t_alldata	*initialize(int argc, char *argv[], char *envp[],
		t_alldata *all_data)
{
	(void)argv;
	if (argc > 1)
	{
		ft_fprintf(STDERR_FILENO, "Too many args");
		exit(127);
	}
	all_data->env_head = NULL;
	// have to be like this or segfault
	all_data->env_list = &all_data->env_head;
	// have to be like this or segfault
	all_data->input = NULL;
	init_envlist(all_data->env_list, envp);
	add_envvar(all_data->env_list, "?", "init");
	// this function is momentarily in env.c
	return (all_data);
}

/**
 * currently the main function is getting confusing.
 */
void	print_command_table(t_cmdtable *table)
{
	t_command		*cmd;
	t_redirection	*redir;
	int				i;

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

/**
 * A static pointer can be avoided if explicitly passing the t_alldata pointer.
 * However, signal handlers don't take arguments. 
 * static variable to store the pointer to t_alldata
 */
static t_alldata *g_all_data_ptr = NULL;

/**
 * Helper function for signals to pass the all_data structs because signals
 * take no arguments.
 * Set a static pointer
 */
void set_alldata(t_alldata *all_data)
{
	g_all_data_ptr = all_data;
}

/**
 * Helper function for signals to pass the all_data structs because signals
 * take no arguments.
 * retrieve the pointer to t_alldata
 */
t_alldata *get_alldata(void)
{
	return g_all_data_ptr;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_alldata	*all_data;
	char		*ex_stat;
	
	setup_signals(); // Set up signal handlers
	all_data = malloc_perex(sizeof(t_alldata), "Malloc error on all_data");
	all_data = initialize(argc, argv, envp, all_data);
	set_alldata(all_data);
	setup_signals(); // Set up signal handlers
	while (1)
	{
		all_data->input = prompt_hist(all_data->input);
		all_data->tokens = lexer(all_data->input);
		all_data->tree = parse(all_data->tokens, all_data);
		all_data->table = ast_to_command_table(all_data->tree);
		// print_command_table(all_data->table);
		all_data->exit_stat = exec_commtab(all_data->table, all_data->env_list,
				envp);
		ex_stat = ft_itoa(all_data->exit_stat);
		add_envvar(all_data->env_list, "?", ex_stat);
		free(ex_stat);
		free_tkn(all_data->tokens);
		free(all_data->input);
		free_command_table(all_data->table);
		free_ast(all_data->tree);
		//printf("all_data->exit_stat:%d", all_data->exit_stat);
	}
	free_envlist(*all_data->env_list);
	free(all_data->env_list);
	free(all_data);
	rl_clear_history();
	return (0);
}
