/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:28:10 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/17 13:47:42 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/**
 * syntax_error_at:
 * ----------------
 * Prints a syntax error message that includes the position in the input
 * where the error occurred. This is useful for more pinpointed error reporting
 * and debugging, indicating exactly where parsing went wrong.
 */

void	syntax_error_at(int position, const char *message)
{
	ft_fprintf(STDERR_FILENO, "Syntax error at position %d: %s\n",
		position, message);
}
