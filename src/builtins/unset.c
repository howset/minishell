/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:32:54 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/15 16:57:09 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/*
 * rh_unset() - Removes environment variables from env_list
 *
 * Parameters:
 *   args[]: Array of command arguments where:
 *          - args[0] is "unset"
 *          - args[1] onwards are variable names to remove
 *   env_list: Double pointer to environment variable list
 *
 * Function flow:
 * 1. Starts from args[1] (skips command name)
 * 2. For each argument, calls remove_envvar() to delete from env_list
 * 3. Continues until all arguments are processed
 *
 * Return: Always returns EXIT_SUCCESS (0)
 *
 * Example usage:
 *   unset PATH PWD  // Removes PATH and PWD variables
 */

int	rh_unset(char *args[], t_env **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_envvar(args[i], env_list);
		i++;
	}
	return (EXIT_SUCCESS);
}
