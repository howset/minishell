/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_perex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:53:42 by reldahli          #+#    #+#             */
/*   Updated: 2024/11/26 21:08:11 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// malloc with perror and exit, to shorten things up

/**
 * Allocates memory of the specified size and prints
 * an error message if the allocation fails.
 * @param bytes The number of bytes to allocate.
 * @param msg The error message to print if the allocation fails.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*malloc_perex(size_t bytes, char *msg)
{
	void	*res;

	res = malloc(bytes);
	if (res == NULL)
	{
		perror(msg);
		exit(EXIT_FAILURE);
	}
	return (res);
}
