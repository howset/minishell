/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:34:01 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 19:34:52 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/**
 * @function process_env_variable
 * @description Replaces an environment variable in
 * the string with its corresponding value.
 * @param {char*} result - The string containing a `$VAR`.
 * @param {int*} i - Pointer to the current index in the string.
 * @param {t_alldata*} all_data - Holds environment data for variable lookup.
 * @return {char*} A new string with the environment variable expanded,
	if found.
 */
char	*process_env_variable(char *result, int *i, t_alldata *all_data)
{
	char	var_name[256];
	t_env	*env;
	char	*new_str;
	int		var_len;
	int		value_len;

	if (!extract_var_name(result, i, var_name))
		return (result);
	env = find_envvar(*all_data->env_list, var_name);
	var_len = ft_strlen(var_name);
	if (env)
		value_len = ft_strlen(env->val);
	else
		value_len = 0;
	new_str = malloc(ft_strlen(result) - var_len + value_len + 1);
	if (!new_str)
		return (result);
	ft_memcpy(new_str, result, *i - var_len - 1);
	if (env)
		ft_memcpy(new_str + (*i - var_len - 1), env->val, value_len);
	ft_memcpy(new_str + (*i - var_len - 1) + value_len, result + *i,
		ft_strlen(result + *i) + 1);
	free(result);
	*i = (*i - var_len - 1) + value_len;
	return (new_str);
}

/**
 * @function handle_special_char
 * @description Examines the current character and
 * delegates processing to the appropriate function.
 * @param {char*} result - The string to process.
 * @param {int*} i - Pointer to the current index in the string.
 * @param {t_alldata*} all_data - Holds environment data for expansions.
 * @return {char*} A new string with special characters properly handled.
 */
char	*handle_special_char(char *result, int *i, t_alldata *all_data)
{
	if (result[*i] == '\"')
		result = process_double_quotes(result, i, all_data);
	else if (result[*i] == '\'')
		result = process_single_quotes(result, i);
	else if (result[*i] == '$')
	{
		(*i)++;
		if (result[*i] == '?')
			result = process_exit_status(result, i, all_data);
		else
			result = process_env_variable(result, i, all_data);
		return (result);
	}
	(*i)++;
	return (result);
}

/**
 * @function sanitize_text
 * @description Preprocesses the input string by handling
 *  quotes and environment variables before parsing.
 * @param {char*} text - The original text to sanitize.
 * @param {t_alldata*} all_data - Holds environment data for expansions.
 * @return {char*} A new string with quotes removed
 * and environment variables expanded.
 */
char	*sanitize_text(char *text, t_alldata *all_data)
{
	char	*result;
	int		i;

	if (!text)
		return (NULL);
	result = ft_strdup(text);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
		result = handle_special_char(result, &i, all_data);
	return (result);
}
