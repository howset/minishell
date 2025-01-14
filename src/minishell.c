/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:09:08 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/14 21:49:06 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (all_data);
}

void	process_input(t_alldata *all_data)
{
	all_data->tokens = lexer(all_data->input);
	all_data->tree = parse(all_data->tokens, all_data);
	all_data->table = ast_to_command_table(all_data->tree);
}

void	update_exit_status(t_alldata *all_data, char *envp[])
{
	char	*ex_stat;

	all_data->exit_stat = exec_commtab(all_data->table, all_data->env_list,
			envp);
	ex_stat = ft_itoa(all_data->exit_stat);
	add_envvar(all_data->env_list, "?", ex_stat);
	free(ex_stat);
}

void	cleanup_iteration(t_alldata *all_data)
{
	free_tkn(all_data->tokens);
	free(all_data->input);
	free_command_table(all_data->table);
	free_ast(all_data->tree);
}

void	cleanup_final(t_alldata *all_data)
{
	free_envlist(*all_data->env_list);
	free(all_data->env_list);
	free(all_data);
	rl_clear_history();
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
		process_input(all_data);
		update_exit_status(all_data, envp);
		cleanup_iteration(all_data);
	}
	cleanup_final(all_data);
	return (0);
}
