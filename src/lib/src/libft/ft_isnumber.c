/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:19:53 by reldahli          #+#    #+#             */
/*   Updated: 2025/01/13 01:13:48 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**An extension of ft_isdigit but includes checks to *str if its empty or NULL.
 * As well, to skip (-). Hate to use pointers to iterate the str, but have to
 * because of ft_isdigit -___-
 * 		Takes *str.
 * 		Returns 0 if no numeric char is found, 1 if found.
 */

int	ft_isnumber(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
