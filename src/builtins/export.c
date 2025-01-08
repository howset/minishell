/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:34:17 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/08 16:29:06 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/*
 * add_env_variables() checks if the environment variable key is valid,
 * then calls add_envvar() to add it to env_list with the given value.
 */
static int	add_env_variables(t_env **env_list, char *key, char *val)
{
	int	i;

	if (!ft_isalpha(*key) && *key != '_')
	{
		// ft_fprintf(STDERR_FILENO, "export: '%s'", key);
		ft_fprintf(STDERR_FILENO, " not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			// ft_fprintf(STDERR_FILENO, "export: '%s'", key);
			ft_fprintf(STDERR_FILENO, " not a valid identifier\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	add_envvar(env_list, key, val);
	return (EXIT_SUCCESS);
}

/*
 * handle_with_equals() temporarily replaces '=' with '\0' so we can split
 * the argument into 'key' and 'value'. If 'value' is empty, we pass NULL
 * to add_env_variables(). Then it restores '='.
 */
static void	handle_with_equals(t_env **env_list, char *arg, char *eq_sign)
{
	char	*value;

	*eq_sign = '\0';
	value = eq_sign + 1;
	if (*value == '\0')
		add_env_variables(env_list, arg, NULL);
	else
		add_env_variables(env_list, arg, value);
	*eq_sign = '=';
}

/*
 * rh_export() implements the 'export' builtin.
 *  - If no arguments are given (beyond the command itself),
 *    it prints the environment list in sorted order.
 *  - Otherwise, it checks each arg for an '=' sign.
 *    If found, handle_with_equals() is used;
 *    if not, the variable is added with a NULL value.
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
			add_env_variables(env_list, args[i], NULL);
	}
	return (EXIT_SUCCESS);
}
