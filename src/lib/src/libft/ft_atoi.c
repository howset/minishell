/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:02:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:47:07 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	i;
	int	sign;

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
}

/*
The  atoi()  function  converts  the initial portion of the
string pointed to by nptr to int.
*/

/*
#include <stdio.h>
#include <stdlib.h> //atoi

int main() 
{
    const char *str1 = "--54";
    const char *str2 = "+789";
    const char *str3 = "++47";

    int num1 = atoi(str1);
    int num2 = atoi(str2);
    int num3 = atoi(str3);
	int num4 = ft_atoi(str1);
	int num5 = ft_atoi(str2);
	int num6 = ft_atoi(str3);

    printf("Converted integers:\n");
    printf("atoi num1: %d\n", num1);  // Prints 12345
    printf("atoi num2: %d\n", num2);  // Prints -6789
    printf("atoi num3: %d\n", num3);  // Prints 42
	printf("ft_atoi num4: %d\n", num4);  // Prints 12345
    	printf("ft_atoi num5: %d\n", num5);  // Prints -6789
    	printf("ft_atoi num6: %d\n", num6);  // Prints 42

    return 0;
}
*/
