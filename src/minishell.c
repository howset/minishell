/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/16 15:59:42 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	g_signal_stat;

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
		exit(0); // may have to free something?
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
	all_data->env_list = &all_data->env_head;
	all_data->input = NULL;
	init_envlist(all_data->env_list, envp);
	add_envvar(all_data->env_list, "?", "0");
	//add_envvar(all_data->env_list, "?", ft_itoa(all_data->exit_stat));
	return (all_data);
}

/**
 * currently the main function is getting confusing.
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_alldata	*all_data;
	char		*ex_stat;

	all_data = malloc_perex(sizeof(t_alldata), "Malloc error on all_data");
	all_data = initialize(argc, argv, envp, all_data);
	setup_signals(all_data->env_list);
	while (1)
	{
		all_data->input = prompt_hist(all_data->input);
		all_data->tokens = lexer(all_data->input);
		//print_tkn(all_data->tokens);
		all_data->tree = parse(all_data->tokens, all_data);
		//print_ast(all_data->tree, 0);
		all_data->table = ast_to_command_table(all_data->tree);
		//print_command_table(all_data->table);
		all_data->exit_stat = exec_commtab(all_data->table, all_data->env_list,
				envp);
		ex_stat = ft_itoa(all_data->exit_stat);
		add_envvar(all_data->env_list, "?", ex_stat);
		free(ex_stat);
		free_tkn(all_data->tokens);
		free(all_data->input);
		free_command_table(all_data->table);
		free_ast(all_data->tree);
	}
	free_envlist(*all_data->env_list);
	free(all_data->env_list);
	free(all_data);
	rl_clear_history();
	return (0);
}
