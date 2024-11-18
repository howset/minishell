/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:11:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:08:37 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_di(int nbr)
{
	char	*res;
	int		cnt;

	res = ft_itoa(nbr);
	cnt = ft_printf_s(res);
	free (res);
	return (cnt);
}
