/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:11:09 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:08:39 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_hex(unsigned int nbr, char lett_case)
{
	char			*base16;
	int				i;
	unsigned int	div;
	unsigned int	mod;

	if (lett_case == 'x')
		base16 = "0123456789abcdef";
	else
		base16 = "0123456789ABCDEF";
	i = 0;
	if (nbr > 15)
	{
		div = nbr / 16;
		i = i + ft_printf_hex(div, lett_case);
	}
	mod = nbr % 16;
	i = i + ft_printf_c(base16[mod]);
	return (i);
}
