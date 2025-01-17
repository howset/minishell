/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 19:21:53 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief Parses the input data and constructs the necessary structures.
 *
 * This function takes the input data from the `all_data` structure, performs
 * lexical analysis to generate tokens, parses these tokens to create an
 * abstract syntax tree (AST), and then converts the AST into a command table.
 *
 * @param all_data A pointer to the `t_alldata` structure containing the input
 *                 data and the resulting tokens, AST, and command table.
 */
void	parse(t_alldata *all_data)
{
	all_data->tokens = lexer(all_data->input);
	all_data->tree = parser(all_data->tokens, all_data);
	all_data->table = ast_to_command_table(all_data->tree);
}

/**
 * @brief Executes the command table and updates the environment variable with
 * 			the exit status.
 *
 * This function executes the command table stored in `all_data->table` using
 * the provided environment variables `envp`. It then converts the exit status
 * to a string and updates the environment variable "?" with this exit status.
 * Finally, it frees the memory allocated for the exit status string.
 *
 * @param all_data Pointer to the structure containing all necessary data for 
 * 					execution.
 * @param envp Array of environment variables.
 */
void	execute(t_alldata *all_data, char *envp[])
{
	char	*ex_stat;

	all_data->exit_stat = exec_commtab(all_data->table, all_data->env_list,
			envp);
	ex_stat = ft_itoa(all_data->exit_stat);
	add_envvar(all_data->env_list, "?", ex_stat);
	free(ex_stat);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_alldata	*all_data;

	all_data = malloc_perex(sizeof(t_alldata), "Malloc error on all_data");
	all_data = initialize(argc, argv, envp, all_data);
	setup_signals(all_data->env_list);
	while (1)
	{
		all_data->input = prompt_hist(all_data->input);
		parse(all_data);
		execute(all_data, envp);
		cleanup_iteration(all_data);
	}
	cleanup_final(all_data);
	return (0);
}
