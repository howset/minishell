/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:04:30 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:53:08 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
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
	if (longn < 0)
		longn = -longn;
	i = len - 1;
	while (longn != 0)
	{
		res[i] = ((longn % 10) + 48);
		longn = longn / 10;
		i--;
	}
	if (n < 0)
		res[0] = '-';
	res[len] = 0;
	return (res);
}

/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/
/*
#include <stdio.h>
int main(void) {
	int n;
	char *res;
	
	//n = 332;
	//n = -813;
	//n = 0;
	res = ft_itoa(n);
	
	printf("Number: %d, Result: %s\n", n, res);
    
    free(res);
    return 0;
}
*/
