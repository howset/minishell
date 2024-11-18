/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:02:53 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:51:58 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*res;

	res = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		res = malloc(sizeof(char) * (j - i + 1));
		if (res == NULL)
			return (NULL);
		if (res)
			ft_strlcpy(res, &s1[i], j - i + 1);
	}
	return (res);
}

/*
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
*/

/*
#include <stdio.h>

int	main(void)
{
	char str1[] = "referencesforfunctionsref";
	//char str2[] = "for";
	char str2[] = "ref";
	char *res;

	printf("\nstr1: %s", str1);
	printf("\nstr2: %s", str2);
	
	res = ft_strtrim(str1, str2);
	
	printf("\nres: %s", res);
	
	free(res);
	return 0;
}
*/
