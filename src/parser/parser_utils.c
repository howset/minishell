/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:28:10 by reldahli          #+#    #+#             */
/*   Updated: 2024/12/29 18:57:29 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"
#include <string.h> //TODO :REMOVE

/**
 * consume_token:
 * --------------
 * Advances the current token pointer to the next token in the linked list.
 * If the current token pointer is NULL, it does nothing. This is used to
 * move forward through the token stream during parsing.
 */

void	consume_token(t_token **current)
{
	if (*current != NULL)
	{
		*current = (*current)->next;
	}
}

/**
 * get_token_type:
 * ---------------
 * Returns the type of the current token. If the current token pointer is NULL,
 * it returns TKN_EOF (end of file). This helps the parser identify the kind
 * of token it is currently looking at without advancing.
 */

t_tkntype	get_token_type(t_token **current)
{
	if (*current != NULL)
	{
		return ((*current)->type);
	}
	return (TKN_EOF);
}

/**
 * parse_error:
 * ------------
 * Prints a parse error message to stderr, indicating the token value (if
 * available) that caused the error. This function assists in debugging and
 * error handling by pointing out the source of parsing failures.
 */

void	parse_error(const char *message, t_token *token)
{
	if (token && token->value)
	{
		fprintf(stderr, "Parse error near '%s': %s\n", token->value, message);
	}
	else
	{
		fprintf(stderr, "Parse error: %s\n", message);
	}
	// TODO FOR LATER: Handle error as needed (e.g., set an error flag,
	// clean up, etc.)
}

/**
 * syntax_error:
 * -------------
 * Prints a syntax error message to stderr. Used when the parser detects that
 * the structure of the tokens does not conform to the expected grammar, but
 * no specific token is highlighted.
 */

void	syntax_error(const char *message)
{
	fprintf(stderr, "Syntax error: %s\n", message);
}

/**
 * syntax_error_at:
 * ----------------
 * Prints a syntax error message that includes the position in the input
 * where the error occurred. This is useful for more pinpointed error reporting
 * and debugging, indicating exactly where parsing went wrong.
 */

void	syntax_error_at(int position, const char *message)
{
	fprintf(stderr, "Syntax error at position %d: %s\n", position, message);
}

void	free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->args)
	{
		for (int i = 0; i < ast->args_count; i++)
		{
			free(ast->args[i]);
		}
		free(ast->args);
	}
	if (ast->filename)
		free(ast->filename);
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}

/**

	* This function is used to sanitize the text that is passed to the parser. It takes a string and replaces

	* all environment variables with their values. If an environment variable is not found,
	it is replaced with

	* an empty string. This function is used to preprocess the input before parsing.
 */
char	*sanitize_text(char *text, t_alldata *all_data)
{
	char	*result;
	int		i;
	int		j;
	char	var_name[256];
	t_env	*env;
	char	*new_str;
	int		var_len;
	int		value_len;

	if (!text)
		return (NULL);
	result = strdup(text);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
		{
			j = 0;
			i++;
			if (result[i] == '?')
			{
				env = find_envvar(*all_data->env_list, "?");
				if (env)
				{
					new_str = malloc(strlen(result) - 1 + ft_strlen(env->val)
							+ 1);
					if (!new_str)
						return (result);
					ft_memcpy(new_str, result, i - 1);
					ft_memcpy(new_str + i - 1, env->val, ft_strlen(env->val));
					ft_memcpy(new_str + i - 1 + ft_strlen(env->val), result + i
						+ 1, ft_strlen(result + i + 1) + 1);
					free(result);
					result = new_str;
					i = i - 1 + ft_strlen(env->val);
					continue ;
				}
			}
			while (result[i] && (ft_isalnum(result[i]) || result[i] == '_'))
			{
				var_name[j++] = result[i++];
			}
			var_name[j] = '\0';
			if (j > 0)
			{
				env = find_envvar(*all_data->env_list, var_name);
				var_len = ft_strlen(var_name);
				value_len = env ? ft_strlen(env->val) : 0;
				new_str = malloc(strlen(result) - var_len + value_len + 1);
				if (!new_str)
					return (result);
				ft_memcpy(new_str, result, i - var_len - 1);
				if (env)
					ft_memcpy(new_str + (i - var_len - 1), env->val, value_len);
				ft_memcpy(new_str + (i - var_len - 1) + value_len, result + i,
					ft_strlen(result + i) + 1);
				free(result);
				result = new_str;
				i = (i - var_len - 1) + value_len;
				continue ;
			}
			continue ;
		}
		i++;
	}
	return (result);
}
