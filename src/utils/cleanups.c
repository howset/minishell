/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:09:17 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/01/17 19:15:47 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

/**
 * @brief Cleans up resources allocated during a single iteration of the shell.
 *
 * This function frees the memory allocated for tokens, input, command table,
 * and abstract syntax tree (AST) in the provided `t_alldata` structure.
 *
 * @param all_data A pointer to the `t_alldata` structure containing the 
 * 					resources to be freed.
 */
void	cleanup_iteration(t_alldata *all_data)
{
	free_tkn(all_data->tokens);
	free(all_data->input);
	free_command_table(all_data->table);
	free_ast(all_data->tree);
}

/**
 * @brief Cleans up and frees all allocated memory and resources.
 *
 * This function performs the final cleanup by freeing the environment list,
 * the environment list pointer, and the main data structure. It also clears
 * the readline history.
 *
 * @param all_data Pointer to the main data structure containing all necessary
 *                 information and resources to be cleaned up.
 */
void	cleanup_final(t_alldata *all_data)
{
	free_envlist(*all_data->env_list);
	free(all_data->env_list);
	free(all_data);
	rl_clear_history();
}
