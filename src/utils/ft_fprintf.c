/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:06:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/12/10 15:04:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	conv_id_check(int fd, const char c, va_list varg);
static int	ft_fprintf_c(int fd, int c);
static int	ft_fprintf_s(int fd, char *str);
static int	ft_fprintf_di(int fd, int nbr);

/**Just a reimplementation of ft_printf to imitate fprintf (prints to fd).
 * Works all the same, but ditched the unnecesary parts (print pointers, hex)
 */
int	ft_fprintf(int fd, const char *fmt, ...)
{
	const char	*str;
	va_list		varg;
	int			i;
	int			printed_chars;

	str = ft_strdup(fmt);
	if (!str)
		return (0);
	va_start(varg, fmt);
	i = 0;
	printed_chars = 0;
	while (str[i])
	{
		if (str[i] != '%')
			printed_chars = printed_chars + ft_fprintf_c(fd, str[i]);
		else if (str[i] == '%')
		{
			printed_chars = printed_chars + conv_id_check(fd, str[i + 1], varg);
			i++;
		}
		i++;
	}
	va_end(varg);
	free((void *)str);
	return (printed_chars);
}

static int	conv_id_check(int fd, const char c, va_list var_arg)
{
	int		cnt;

	cnt = 0;
	if (c == 'c')
		cnt = ft_fprintf_c(fd, va_arg(var_arg, int));
	else if (c == 's')
		cnt = ft_fprintf_s(fd, va_arg(var_arg, char *));
	else if (c == 'd' || c == 'i')
		cnt = ft_fprintf_di(fd, va_arg(var_arg, int));
	else if (c == '%')
	{
		write(1, "%", 1);
		cnt = 1;
	}
	return (cnt);
}

static int	ft_fprintf_c(int fd, int c)
{
	ft_putchar_fd(c, fd);
	return (1);
}

static int	ft_fprintf_s(int fd, char *str)
{
	int	cnt;

	if (!str)
		return (write(1, "(null)", 6));
	cnt = 0;
	while (str[cnt] != '\0')
		cnt = cnt + ft_fprintf_c(fd, str[cnt]);
	return (cnt);
}

static int	ft_fprintf_di(int fd, int nbr)
{
	char	*res;
	int		cnt;

	res = ft_itoa(nbr);
	cnt = ft_fprintf_s(fd, res);
	free (res);
	return (cnt);
}
