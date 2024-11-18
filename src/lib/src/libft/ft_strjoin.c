/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:01:19 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:51:40 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

/*
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/

/*
#include <stdio.h>

int	main(void)
{
	//char str1[] = "dogdog";
	//char str2[] = "catcat";
	char str1[] = "dogdogdogdogdogdogdogdogdogdogdogdog";
	char str2[] = "catcatcatcatcatcatcatcatcatcatcatcat";
	char *res;

	printf("\nstr1: %s", str1);
	printf("\nstr2: %s", str2);
	
	res = ft_strjoin(str2, str1);
	
	printf("\nres: %s", res);
	
	free(res);
	return 0;
}
*/
