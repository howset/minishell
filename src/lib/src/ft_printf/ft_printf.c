/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:06:31 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/22 14:08:49 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conv_id_check(const char c, va_list varg);

int	ft_printf(const char *fmt, ...)
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
			printed_chars = printed_chars + ft_printf_c(str[i]);
		else if (str[i] == '%')
		{
			printed_chars = printed_chars + conv_id_check(str[i + 1], varg);
			i++;
		}
		i++;
	}
	va_end(varg);
	free((void *)str);
	return (printed_chars);
}

static int	conv_id_check(const char c, va_list var_arg)
{
	int		cnt;

	cnt = 0;
	if (c == 'c')
		cnt = ft_printf_c(va_arg(var_arg, int));
	else if (c == 's')
		cnt = ft_printf_s(va_arg(var_arg, char *));
	else if (c == 'p')
		cnt = ft_printf_p(va_arg(var_arg, void *));
	else if (c == 'd' || c == 'i')
		cnt = ft_printf_di(va_arg(var_arg, int));
	else if (c == 'u')
		cnt = ft_printf_u(va_arg(var_arg, unsigned int));
	else if (c == 'x' || c == 'X')
		cnt = ft_printf_hex(va_arg(var_arg, int), c);
	else if (c == '%')
	{
		write(1, "%", 1);
		cnt = 1;
	}
	return (cnt);
}

/*
#include <limits.h>
int main (void)
{
//printf("\nPrintf printed_chars:%d", printed_chars); //under free((void *)str);
    //printf("printf char: %c\n", 'h'); 
    //ft_printf("ft_printf char: %c", 'h'); //n=17
    //ft_printf("test sentence %c %c", 'H', 'M'); //n=1
    //ft_printf("test sentence %%"); //n=15
    
    //ft_printf("8letters %s %s", "8letters", "8letters"); //n=26
    
    //printf("i: %d", i);
    //ft_printf("test sentence %d", 5); //n=15
    //ft_printf("test sentence %d", 17); //n=16
    //ft_printf("test sentence %d", 200); //n=17
    //ft_printf("test sentence %d", -200); //n=18
    //ft_printf("test sentence %d", INT_MIN);
    
    //ft_printf("test sentence %u", UINT_MAX);
    
    //char i = 'h';
    //char *pI;
    //pI = &i;
    //printf("P add pI: %p", pI);
    //printf("\n");
    //printf("P add &i: %p", &i);
    //printf("\n");
    //printf("Val *pI:%c", *pI);
    //printf("\n");
    //printf("Val i:%c", i);

    //int n = 479;
    //ft_printf("479 should be 1df: %x ", n); //n=1
    //ft_printf("479 should be 1DF: %X ", n); //n=1
    //int n = 894;
    //ft_printf("894 should be 37e: %x ", n); //n=1
    //ft_printf("894 should be 37E: %X ", n); //n=1

	//int	chars_written;
    
    void *mem_add;
	mem_add = malloc(sizeof(char));
    //chars_written = ft_printf(memory_address);
    //free(memory_address);
	//printf("Chars written:%d", chars_written);
	ft_printf("Pointer ft_printf: %p", mem_add);
	printf("\n");
	printf("Pointer printf: %p", mem_add);

	//void* null_pointer = NULL;
    //chars_written = ft_printf(null_pointer);
}
*/
/*
ccexa -n ft_printf.c ./libft/ft_putchar_fd.c 
./libft/ft_strdup.c ft_printf_c.c ./libft/ft_strlen.c
./libft/ft_strlcpy.c ft_printf_s.c ft_printf_di.c
./libft/ft_itoa.c ft_printf_u.c ft_printf_hex.c
*/
