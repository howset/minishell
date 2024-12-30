/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:32:54 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/30 15:18:17 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/**This imitation of unset basically just tries to match the given key to the
 * key-value pair in the env_list. If the key is found, then remove the
 * key-value pair. If it is not found, do nothing.
 * 		Takes the args from the simple command and env_list.
 * 		Returns the exit status (always 0, except when no args given)
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
