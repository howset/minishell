/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:00:55 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/05/08 17:03:25 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* long	ft_atol(const char *nptr)
{
	long	res;
	int		i;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	res = res * sign;
	return (res);
} */

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (8192);
	return (0);
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	i += (nptr[i] == '+' || nptr[i] == '-');
	if (ft_isdigit(nptr[i]) == 0)
		return (LONG_MAX);
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] && ft_isascii(nptr[i]))
		return (LONG_MAX);
	res *= sign;
	return (res);
}
