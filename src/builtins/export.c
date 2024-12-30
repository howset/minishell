/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:34:17 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/30 12:02:02 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

static void	handle_with_equals(t_env **env_list, char *arg, char *eq_sign)
{
	char	*value;

	*eq_sign = '\0';
	value = eq_sign + 1;
	if (*value == '\0')
		add_envvar(env_list, arg, NULL);
	else
		add_envvar(env_list, arg, value);
	*eq_sign = '=';
}

/**This is the implementation of export. It either prints env_list when no args
 * are given in the simple command, or add/update the env_list if there is one.
 * When that happens, the func loops over the args and finds the eq sign. The
 * eq_sign is then replaced with a null terminator to split the string to key
 * (args[i]) and value (eq_sign+1) which then are passed to add_envvar. The
 * eq_sign is then restored to =. If no eq sign is found, then add_envvar is
 * called without val.
 * 		Takes the whole args in simple command (incl args[0] --> the command,
 * 			has to be skipped, hence the check for args[1]), and env_list.
 * 		Returns 0 because always success that will be transferred to the
 * 			calling executor.
 */
int	rh_export(char *args[], t_env **env_list)
{
	int		i;
	char	*eq_sign;

	if (!args[1])
	{
		print_sortedenvlist(*env_list);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (args[++i])
	{
		eq_sign = ft_strchr(args[i], '=');
		if (eq_sign)
			handle_with_equals(env_list, args[i], eq_sign);
		else
			add_envvar(env_list, args[i], NULL);
	}
	return (EXIT_SUCCESS);
}
