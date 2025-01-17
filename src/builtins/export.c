/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 04:34:17 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 15:23:06 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

/*
 * add_env_variables() - Validates and adds environment variables to env list
 *
 * Parameters:
 *   env_list: Double pointer to environment variable list
 *   key: Environment variable name to add/update
 *   val: Value to associate with the key
 *
 * Return values:
 *   EXIT_SUCCESS (0): Variable added successfully
 *   EXIT_FAILURE (1): Invalid identifier
 *
 * Function flow:
 * 1. Validate key's first character:
 *    - Must start with letter or underscore
 *    - Returns failure if invalid
 *
 * 2. Validate remaining characters in key:
 *    - Must be alphanumeric or underscore
 *    - Exits with failure if invalid character found
 *
 * 3. If validation passes:
 *    - Calls add_envvar() to add/update environment variable
 *    - Returns success
 *
 * Valid format examples:
 *   - "PATH=/usr/bin"     (valid)
 *   - "_TEST=value"       (valid)
 *   - "2TEST=value"       (invalid)
 *   - "TEST@=value"       (invalid)
 */

static int	add_env_variables(t_env **env_list, char *key, char *val)
{
	int	i;

	if (!ft_isalpha(*key) && *key != '_')
	{
		ft_fprintf(STDERR_FILENO, " not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
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

static int	handle_with_equals(t_env **env_list, char *arg, char *eq_sign)
{
	char	*value;

	*eq_sign = '\0';
	value = eq_sign + 1;
	if (*value == '\0')
	{
		if (add_env_variables(env_list, arg, NULL) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (add_env_variables(env_list, arg, value) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	*eq_sign = '=';
	return (EXIT_SUCCESS);
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
		{
			if (handle_with_equals(env_list, args[i], eq_sign) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		else
		{
			if (add_env_variables(env_list, args[i], NULL) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
