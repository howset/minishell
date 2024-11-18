/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:37:44 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:06:24 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> /*variable arguments*/
# include "../libft/libft.h"

int	ft_printf(const char *fmt, ...);
int	ft_printf_c(int c);
int	ft_printf_s(char *str);
int	ft_printf_di(int n);
int	ft_printf_u(unsigned int n);
int	ft_printf_hex(unsigned int nbr, char lett_case);
int	ft_printf_p(void *ptr);

#endif
