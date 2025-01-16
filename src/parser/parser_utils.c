/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:28:10 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/16 18:25:28 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

/**
 * consume_token:
 * --------------
 * Advances the current token pointer to the next token in the linked list.
 * If the current token pointer is NULL, it does nothing. This is used to
 * move forward through the token stream during parsing.
 */
/* void	consume_token(t_token **current)
{
	if (*current != NULL)
	{
		*current = (*current)->next;
	}
} */

/**
 * get_token_type:
 * ---------------
 * Returns the type of the current token. If the current token pointer is NULL,
 * it returns TKN_EOF (end of file). This helps the parser identify the kind
 * of token it is currently looking at without advancing.
 */
/* t_tkntype	get_token_type(t_token **current)
{
	if (*current != NULL)
	{
		return ((*current)->type);
	}
	return (TKN_EOF);
} */

/**
 * parse_error:
 * ------------
 * Prints a parse error message to stderr, indicating the token value (if
 * available) that caused the error. This function assists in debugging and
 * error handling by pointing out the source of parsing failures.
 * To do for later: Handle error as needed (e.g., set an error flag,clean up,
 * etc.)
 */

/* void	parse_error(const char *message, t_token *token)
{
	if (token && token->value)
	{
		fprintf(stderr, "Parse error near '%s': %s\n", token->value, message);
	}
	else
	{
		fprintf(stderr, "Parse error: %s\n", message);
	}
} */

/**
 * syntax_error_at:
 * ----------------
 * Prints a syntax error message that includes the position in the input
 * where the error occurred. This is useful for more pinpointed error reporting
 * and debugging, indicating exactly where parsing went wrong.
 */

void	syntax_error_at(int position, const char *message)
{
	ft_fprintf(STDERR_FILENO, "Syntax error at position %d: %s\n", position, message);
}
