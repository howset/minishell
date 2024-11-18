/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:11:07 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:08:46 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_getlen(long longn);
static char	*ft_itoa_u(unsigned int n);

int	ft_printf_u(unsigned int n)
{
	char	*res;
	int		cnt;

	res = ft_itoa_u(n);
	cnt = ft_printf_s(res);
	free (res);
	return (cnt);
}

static int	ft_getlen(long longn)
{
	int	i;

	i = 0;
	if (longn < 0)
	{
		i++;
		longn = -longn;
	}
	if (longn == 0)
		i++;
	while (longn != 0)
	{
		longn = longn / 10;
		i++;
	}
	return (i);
}

static char	*ft_itoa_u(unsigned int n)
{
	int		len;
	int		i;
	char	*res;
	long	longn;

	longn = n;
	len = ft_getlen(longn);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[0] = '0';
	i = len - 1;
	while (longn != 0)
	{
		res[i] = ((longn % 10) + 48);
		longn = longn / 10;
		i--;
	}
	res[len] = 0;
	return (res);
}
