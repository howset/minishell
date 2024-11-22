/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:37:24 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/11/22 14:34:06 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//malloc with perror and exit, to shorten things up
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