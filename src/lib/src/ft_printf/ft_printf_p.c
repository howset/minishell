/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:11:02 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:08:42 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_ptr(unsigned long nbr);

int	ft_printf_p(void *ptr)
{
	unsigned long	nbr;
	int				len;

	if (!ptr)
		return (write(1, "(nil)", 5));
	nbr = (unsigned long)ptr;
	len = ft_printf_s("0x");
	len = len + print_ptr(nbr);
	return (len);
}

static int	print_ptr(unsigned long nbr)
{
	int				len;
	char			*base16;
	unsigned long	div;
	unsigned long	mod;

	len = 0;
	base16 = "0123456789abcdef";
	if (nbr > 15)
	{
		div = nbr / 16;
		len = len + print_ptr(div);
	}
	mod = nbr % 16;
	len = len + ft_printf_c(base16[mod]);
	return (len);
}
