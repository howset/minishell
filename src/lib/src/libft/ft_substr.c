/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:59:17 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/01/11 12:51:17 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*res_ptr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	res = malloc(sizeof(*s) * (len + 1));
	if (res == NULL)
		return (NULL);
	s = s + start;
	res_ptr = res;
	*(res + len) = '\0';
	while (len > 0 && *s != '\0')
	{
		*res++ = *s++;
		len--;
	}
	return (res_ptr);
}

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	res = malloc(sizeof(*s) * (len + 1));
	if (res == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
*/

/*
Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.
*/

/*
#include <stdio.h>

int	main(void)
{
	char str[] = "manipulation_capabilities";
	char *res;

	printf("\nstr: %s", str);
	
	//res = ft_substr(str, 0, 5);
	//res = ft_substr("hola", 0, 18446744073709551615); fails, too big
	
	printf("\nres: %s", res);
	
	free(res);
	return 0;
}
*/
