/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:11:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:08:44 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_s(char *str)
{
	int	cnt;

	if (!str)
		return (write(1, "(null)", 6));
	cnt = 0;
	while (str[cnt] != '\0')
		cnt = cnt + ft_printf_c(str[cnt]);
	return (cnt);
}
