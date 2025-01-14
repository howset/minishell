/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:33:41 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/14 21:39:09 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/**
 * @function extract_and_process_quotes
 * @description Extracts and processes text within double quotes,
	replacing environment variables if needed.
 * @param {char*} result - The original string containing quotes.
 * @param {int*} i - Pointer to the current index in the string.
 * @param {t_alldata*} all_data - Holds environment data for variable expansion.
 * @return {char*} A newly allocated string containing the processed text.
 */
char	*extract_and_process_quotes(char *result, int *i, t_alldata *all_data)
{
	int		start;
	int		len;
	char	*substr;
	char	*processed;

	start = *i + 1;
	len = 0;
	(*i)++;
	while (result[*i] && result[*i] != '\"')
	{
		len++;
		(*i)++;
	}
	substr = ft_substr(result, start, len);
	processed = sanitize_text(substr, all_data);
	free(substr);
	return (processed);
}

/**
 * @function process_double_quotes
 * @description Handles double-quoted parts of the string,
	invoking quote extraction and replacement.
 * @param {char*} result - The current string to process.
 * @param {int*} i - Pointer to the current index in the string.
 * @param {t_alldata*} all_data - Holds environment data for variable expansion.
 * @return {char*} A new string where the double-quoted
 * section is replaced with processed content.
 */
char	*process_double_quotes(char *result, int *i, t_alldata *all_data)
{
	char	*processed;
	char	*new_str;
	int		start;

	start = *i + 1;
	processed = extract_and_process_quotes(result, i, all_data);
	if (!processed)
		return (result);
	new_str = malloc(strlen(result) - ((*i) - start + 2) + strlen(processed)
			+ 1);
	if (!new_str)
	{
		free(processed);
		return (result);
	}
	ft_memcpy(new_str, result, start - 1);
	ft_memcpy(new_str + start - 1, processed, strlen(processed));
	ft_memcpy(new_str + start - 1 + strlen(processed), result + *i + 1,
		strlen(result + *i + 1) + 1);
	free(processed);
	free(result);
	*i = start - 1 + strlen(processed);
	return (new_str);
}

/**
 * @function process_single_quotes
 * @description Handles single-quoted parts of the
 * string by removing the quote characters.
 * @param {char*} result - The current string to process.
 * @param {int*} i - Pointer to the current index in the string.
 * @return {char*} A new string with single
 * quotes removed from the specified section.
 */
char	*process_single_quotes(char *result, int *i)
{
	int		start;
	int		len;
	char	*new_str;

	start = *i + 1;
	len = 0;
	(*i)++;
	while (result[*i] && result[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	new_str = malloc(strlen(result) - 2 + 1);
	if (!new_str)
		return (result);
	ft_memcpy(new_str, result, start - 1);
	ft_memcpy(new_str + start - 1, result + start, len);
	ft_memcpy(new_str + start - 1 + len, result + start + len + 1, strlen(result
			+ start + len + 1) + 1);
	free(result);
	*i = start - 1 + len;
	return (new_str);
}

/**
 * @function process_exit_status
 * @description Replaces the special variable `$?` with
 * the last exit status value.
 * @param {char*} result - The current string to process.
 * @param {int*} i - Pointer to the current index in the string.
 * @param {t_alldata*} all_data - Holds environment data where `?` is stored.\
 * @return {char*} A new string where `$?`
 * is replaced with the stored exit status.
 */
char	*process_exit_status(char *result, int *i, t_alldata *all_data)
{
	t_env	*env;
	char	*new_str;

	env = find_envvar(*all_data->env_list, "?");
	if (!env)
		return (result);
	new_str = malloc(strlen(result) - 1 + ft_strlen(env->val) + 1);
	if (!new_str)
		return (result);
	ft_memcpy(new_str, result, *i - 1);
	ft_memcpy(new_str + *i - 1, env->val, ft_strlen(env->val));
	ft_memcpy(new_str + *i - 1 + ft_strlen(env->val), result + *i + 1,
		ft_strlen(result + *i + 1) + 1);
	free(result);
	*i = *i - 1 + ft_strlen(env->val);
	return (new_str);
}

/**
 * @function extract_var_name
 * @description Extracts a valid environment variable
 * name from the given position in a string.
 * @param {const char*} result
	- The string containing a potential variable name.
 * @param {int*} i - Pointer to the current index in the string.
 * @param {char*} var_name - Buffer to store the extracted name.
 * @return {char*} The extracted name, or NULL if none is found.
 */
char	*extract_var_name(const char *result, int *i, char *var_name)
{
	int	j;

	j = 0;
	while (result[*i] && (ft_isalnum(result[*i]) || result[*i] == '_'))
		var_name[j++] = result[(*i)++];
	var_name[j] = '\0';
	if (j == 0)
		return (NULL);
	return (var_name);
}
